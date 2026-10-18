"""The interactive template: the reference solution is accepted, wrong ones are rejected."""
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
KIT = ROOT / "templates" / "interactive"
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(KIT))

import interact  # noqa: E402
import run_tests  # noqa: E402

INTERACTOR = [sys.executable, str(KIT / "hidden_integer_interactor.py")]
ALWAYS_ONE = '#include <iostream>\nint main() { std::cout << "! 1" << std::endl; }\n'
LINEAR = """#include <bits/stdc++.h>
int main() {
    for (int y = 1;; y++) {
        std::cout << "? " << y << std::endl;
        std::string r;
        std::cin >> r;
        if (r == "NO") { std::cout << "! " << y << std::endl; return 0; }
    }
}
"""


def compile_cpp(src: Path, binary: Path) -> None:
    proc = subprocess.run(["g++", *run_tests.compiler_flags(), str(src), "-o", str(binary)],
                          capture_output=True, text=True)
    if proc.returncode != 0:
        raise AssertionError(proc.stderr)


class InteractiveTemplateTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tmp = tempfile.TemporaryDirectory()
        tmp = Path(cls.tmp.name)
        cls.binaries = {}
        for name, code in [("always_one", ALWAYS_ONE), ("linear", LINEAR)]:
            (tmp / f"{name}.cpp").write_text(code)
        sources = {"reference": KIT / "hidden_integer.cpp",
                   "always_one": tmp / "always_one.cpp", "linear": tmp / "linear.cpp"}
        for name, src in sources.items():
            cls.binaries[name] = str(tmp / name)
            compile_cpp(src, tmp / name)

    @classmethod
    def tearDownClass(cls):
        cls.tmp.cleanup()

    def verdict(self, solution: str, hidden: int) -> int:
        return interact.run(self.binaries[solution], [*INTERACTOR, str(hidden)])

    def test_reference_is_accepted_on_extremes_and_middle(self):
        for hidden in [1, 2, 999_999_999, 1_000_000_000, 123_456_789, 536_870_912]:
            with self.subTest(hidden=hidden):
                self.assertEqual(self.verdict("reference", hidden), 0)

    def test_wrong_answer_is_rejected(self):
        self.assertEqual(self.verdict("always_one", 1), 0)
        self.assertEqual(self.verdict("always_one", 2), 1)

    def test_too_many_questions_is_rejected(self):
        self.assertEqual(self.verdict("linear", 30), 0)
        self.assertEqual(self.verdict("linear", 31), 1)


if __name__ == "__main__":
    unittest.main()
