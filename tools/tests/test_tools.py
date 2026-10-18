"""Tests for the course tooling. Run: python3 -m unittest discover -s tools/tests"""
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
FIXTURES = Path(__file__).resolve().parent / "fixtures"
STRESS = ROOT / "templates" / "stress"
sys.path.insert(0, str(ROOT / "tools"))

import run_tests  # noqa: E402


class TokensMatchTest(unittest.TestCase):
    def test_ignores_whitespace_differences(self):
        self.assertTrue(run_tests.tokens_match("1 2\n3\n", "1  2 3"))

    def test_detects_different_tokens(self):
        self.assertFalse(run_tests.tokens_match("1 2 3", "1 2 4"))

    def test_detects_missing_tokens(self):
        self.assertFalse(run_tests.tokens_match("1 2 3", "1 2"))


class FindProblemsTest(unittest.TestCase):
    def test_finds_every_directory_with_sol_cpp(self):
        names = [p.name for p in run_tests.find_problems([FIXTURES])]
        self.assertEqual(names, ["any-order", "sum-ok", "sum-wrong"])

    def test_accepts_a_sol_cpp_path(self):
        found = run_tests.find_problems([FIXTURES / "sum-ok" / "sol.cpp"])
        self.assertEqual(found, [FIXTURES / "sum-ok"])


class RunProblemIntegrationTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.flags = run_tests.compiler_flags()

    def run_problem(self, name):
        with tempfile.TemporaryDirectory() as tmp:
            return run_tests.test_problem(FIXTURES / name, "g++", self.flags, Path(tmp))

    def test_correct_solution_passes(self):
        self.assertTrue(all(r.ok for r in self.run_problem("sum-ok")))

    def test_wrong_answer_fails_with_diff(self):
        [result] = self.run_problem("sum-wrong")
        self.assertFalse(result.ok)
        self.assertIn("expected", result.message)

    def test_checker_accepts_alternative_answer(self):
        self.assertTrue(all(r.ok for r in self.run_problem("any-order")))

    def test_runs_without_sanitizers_when_disabled(self):
        env = dict(run_tests.os.environ, SANITIZE="0")
        proc = subprocess.run([sys.executable, str(ROOT / "tools" / "run_tests.py"),
                               str(FIXTURES / "sum-ok")], capture_output=True, env=env)
        self.assertEqual(proc.returncode, 0)

    def test_cli_exit_code_reflects_failures(self):
        ok = subprocess.run([sys.executable, str(ROOT / "tools" / "run_tests.py"),
                             str(FIXTURES / "sum-ok")], capture_output=True)
        bad = subprocess.run([sys.executable, str(ROOT / "tools" / "run_tests.py"),
                              str(FIXTURES / "sum-wrong")], capture_output=True)
        self.assertEqual(ok.returncode, 0)
        self.assertEqual(bad.returncode, 1)


class StressScriptIntegrationTest(unittest.TestCase):
    def stress(self, solution):
        return subprocess.run(
            ["bash", str(STRESS / "stress.sh"), str(solution),
             str(STRESS / "brute_max_subarray.cpp"), str(STRESS / "gen_max_subarray.py"), "200"],
            capture_output=True, text=True,
        )

    def test_finds_counterexample_for_buggy_solution(self):
        proc = self.stress(STRESS / "buggy_max_subarray.cpp")
        self.assertEqual(proc.returncode, 1)
        self.assertIn("MISMATCH", proc.stdout)

    def test_passes_correct_solution(self):
        proc = self.stress(FIXTURES / "kadane_correct.cpp")
        self.assertEqual(proc.returncode, 0, proc.stdout + proc.stderr)
        self.assertIn("OK: 200", proc.stdout)


if __name__ == "__main__":
    unittest.main()
