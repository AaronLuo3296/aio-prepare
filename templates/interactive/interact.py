"""Run an interactive solution against an interactor, the way an online judge does.

Usage: python3 interact.py ./sol interactor.py [interactor args ...]

The solution's stdout is wired to the interactor's stdin and vice versa. The interactor
decides the verdict: exit code 0 = accepted, anything else = wrong answer (it explains why
on stderr). Exit code of this script: 0 accepted, 1 wrong answer, 2 solution crashed or
timed out.
"""
import subprocess
import sys

TIMEOUT_SECONDS = 5


def run(solution, interactor_cmd):
    inter = subprocess.Popen(interactor_cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    sol = subprocess.Popen([solution], stdin=inter.stdout, stdout=inter.stdin)
    inter.stdout.close()                     # the two children now own both pipe ends
    inter.stdin.close()
    try:
        sol_code = sol.wait(timeout=TIMEOUT_SECONDS)
        inter_code = inter.wait(timeout=TIMEOUT_SECONDS)
    except subprocess.TimeoutExpired:
        sol.kill()
        inter.kill()
        print("TIMEOUT (did you forget to flush after each line?)", file=sys.stderr)
        return 2
    if inter_code != 0:
        print("WRONG ANSWER", file=sys.stderr)
        return 1
    if sol_code != 0:
        print(f"RUNTIME ERROR (exit code {sol_code})", file=sys.stderr)
        return 2
    print("ACCEPTED", file=sys.stderr)
    return 0


if __name__ == "__main__":
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    sys.exit(run(sys.argv[1], [sys.executable, *sys.argv[2:]]))
