"""Interactor for CSES "Hidden Integer": python3 hidden_integer_interactor.py X

Answers "? y" with YES if y < X, else NO. Accepts "! X" after at most 30 questions.
"""
import sys

MAX_QUESTIONS = 30
LIMIT = 10**9


def fail(msg):
    print(f"interactor: {msg}", file=sys.stderr)
    sys.exit(1)


def main():
    x = int(sys.argv[1])
    asked = 0
    for line in sys.stdin:
        parts = line.split()
        if len(parts) != 2 or parts[0] not in "?!" or not parts[1].lstrip("-").isdigit():
            fail(f"malformed line {line!r}")
        y = int(parts[1])
        if parts[0] == "!":
            if y != x:
                fail(f"answered {y}, hidden integer was {x}")
            return
        asked += 1
        if asked > MAX_QUESTIONS:
            fail(f"more than {MAX_QUESTIONS} questions")
        if not 1 <= y <= LIMIT:
            fail(f"question {y} out of range")
        print("YES" if y < x else "NO", flush=True)
    fail("solution stopped without answering")


if __name__ == "__main__":
    main()
