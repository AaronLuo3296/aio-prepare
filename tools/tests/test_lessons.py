"""Every complete C++ program (a ```cpp block with main) in lessons/ must compile."""
import re
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import run_tests  # noqa: E402

CPP_BLOCK = re.compile(r"```cpp\n(.*?)```", re.DOTALL)


def lesson_programs():
    for lesson in sorted((ROOT / "lessons").glob("*.md")):
        for i, code in enumerate(CPP_BLOCK.findall(lesson.read_text()), 1):
            if "int main" in code:
                yield lesson.name, i, code


class LessonCodeCompilesTest(unittest.TestCase):
    def test_lessons_contain_programs(self):
        self.assertGreater(len(list(lesson_programs())), 0)

    def test_every_program_compiles(self):
        flags = run_tests.compiler_flags()
        with tempfile.TemporaryDirectory() as tmp:
            for name, i, code in lesson_programs():
                with self.subTest(lesson=name, block=i):
                    src = Path(tmp) / "prog.cpp"
                    src.write_text(code)
                    proc = subprocess.run(
                        ["g++", *flags, "-fsyntax-only", str(src)],
                        capture_output=True, text=True,
                    )
                    self.assertEqual(proc.returncode, 0, proc.stderr)


if __name__ == "__main__":
    unittest.main()
