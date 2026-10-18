"""Compile every reference solution and run it against its sample tests.

Layout of a problem directory (anywhere under solutions/):
    sol.cpp        the solution
    N.in / N.out   test pairs (output compared token by token)
    check.py       optional: for problems with many valid answers, called as
                   `python3 check.py N.in actual_output_file N.out`; exit 0 = accepted

Usage: python3 tools/run_tests.py [path ...]   (default: solutions/)
"""
from __future__ import annotations

import os
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TIMEOUT_SECONDS = 5


@dataclass(frozen=True)
class Result:
    problem: Path
    case: str
    ok: bool
    message: str = ""


def tokens_match(expected: str, actual: str) -> bool:
    return expected.split() == actual.split()


def compiler_flags() -> list[str]:
    out = subprocess.run(
        ["bash", str(ROOT / "tools" / "cxxflags.sh")],
        check=True, capture_output=True, text=True,
    ).stdout
    return [line for line in out.splitlines() if line]


def find_problems(paths: list[Path]) -> list[Path]:
    found = set()
    for path in paths:
        if path.is_file() and path.name == "sol.cpp":
            found.add(path.parent)
        else:
            found.update(p.parent for p in path.rglob("sol.cpp"))
    return sorted(found)


def compile_solution(problem: Path, binary: Path, cxx: str, flags: list[str]) -> str | None:
    proc = subprocess.run(
        [cxx, *flags, "-Werror", "-fsanitize=address,undefined",
         str(problem / "sol.cpp"), "-o", str(binary)],
        capture_output=True, text=True,
    )
    return None if proc.returncode == 0 else proc.stderr


def run_case(problem: Path, binary: Path, case_in: Path, workdir: Path) -> Result:
    case = case_in.stem
    expected_file = case_in.with_suffix(".out")
    try:
        with case_in.open() as stdin:
            proc = subprocess.run(
                [str(binary)], stdin=stdin, capture_output=True,
                text=True, timeout=TIMEOUT_SECONDS,
            )
    except subprocess.TimeoutExpired:
        return Result(problem, case, False, f"timeout after {TIMEOUT_SECONDS}s")
    if proc.returncode != 0:
        return Result(problem, case, False, f"exit code {proc.returncode}\n{proc.stderr}")

    checker = problem / "check.py"
    if checker.exists():
        actual_file = workdir / f"{problem.name}.{case}.actual"
        actual_file.write_text(proc.stdout)
        check = subprocess.run(
            [sys.executable, str(checker), str(case_in), str(actual_file), str(expected_file)],
            capture_output=True, text=True,
        )
        return Result(problem, case, check.returncode == 0, check.stdout + check.stderr)

    if not expected_file.exists():
        return Result(problem, case, False, f"missing {expected_file.name}")
    if tokens_match(expected_file.read_text(), proc.stdout):
        return Result(problem, case, True)
    return Result(problem, case, False,
                  f"expected:\n{expected_file.read_text()}got:\n{proc.stdout}")


def test_problem(problem: Path, cxx: str, flags: list[str], workdir: Path) -> list[Result]:
    binary = workdir / f"{problem.parent.name}-{problem.name}"
    error = compile_solution(problem, binary, cxx, flags)
    if error is not None:
        return [Result(problem, "compile", False, error)]
    cases = sorted(problem.glob("*.in"))
    if not cases:
        return [Result(problem, "-", False, "no *.in test cases")]
    return [run_case(problem, binary, case, workdir) for case in cases]


def main(argv: list[str]) -> int:
    paths = [Path(a).resolve() for a in argv] or [ROOT / "solutions"]
    cxx = os.environ.get("CXX", "g++")
    flags = compiler_flags()
    problems = find_problems(paths)
    if not problems:
        print("no problems found")
        return 1

    failures = 0
    with tempfile.TemporaryDirectory() as tmp:
        for problem in problems:
            results = test_problem(problem, cxx, flags, Path(tmp))
            bad = [r for r in results if not r.ok]
            failures += len(bad)
            status = "PASS" if not bad else "FAIL"
            print(f"{status}  {problem.relative_to(ROOT) if problem.is_relative_to(ROOT) else problem}"
                  f"  ({len(results) - len(bad)}/{len(results)})")
            for r in bad:
                print(f"    case {r.case}: {r.message.strip()}")

    print(f"\n{len(problems)} problems, {failures} failing case(s)")
    return 0 if failures == 0 else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
