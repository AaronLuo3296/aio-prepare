"""The IOI-style grader template: solution + grader link and pass the tests; the stub links."""
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
GRADER = ROOT / "templates" / "grader"
sys.path.insert(0, str(ROOT / "tools"))

import run_tests  # noqa: E402


def build(solution: str, binary: Path) -> subprocess.CompletedProcess:
    return subprocess.run(
        ["g++", *run_tests.compiler_flags(), "-Werror", f"-I{GRADER}",
         str(GRADER / "grader.cpp"), str(GRADER / solution), "-o", str(binary)],
        capture_output=True, text=True,
    )


class GraderTemplateTest(unittest.TestCase):
    def test_reference_solution_passes_every_case(self):
        cases = sorted((GRADER / "tests").glob("*.in"))
        self.assertGreater(len(cases), 0)
        with tempfile.TemporaryDirectory() as tmp:
            binary = Path(tmp) / "meeting"
            proc = build("meeting.cpp", binary)
            self.assertEqual(proc.returncode, 0, proc.stderr)
            for case in cases:
                with self.subTest(case=case.name), case.open() as stdin:
                    out = subprocess.run([str(binary)], stdin=stdin, capture_output=True,
                                         text=True, timeout=run_tests.TIMEOUT_SECONDS).stdout
                    self.assertTrue(run_tests.tokens_match(
                        case.with_suffix(".out").read_text(), out))

    def test_stub_links_against_grader(self):
        with tempfile.TemporaryDirectory() as tmp:
            proc = build("stub.cpp", Path(tmp) / "stub")
            self.assertEqual(proc.returncode, 0, proc.stderr)


if __name__ == "__main__":
    unittest.main()
