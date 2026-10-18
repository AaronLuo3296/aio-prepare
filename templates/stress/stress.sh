#!/usr/bin/env bash
# Stress test: compare a fast solution against a brute force on random inputs.
#
# Usage: stress.sh <solution.cpp> <brute.cpp> <generator.py> [iterations]
# The generator receives the iteration number as its only argument (use it as the
# random seed) and prints one test input to stdout.
# Exits 0 if all iterations agree; exits 1 and prints the failing input otherwise.
set -euo pipefail

if [[ $# -lt 3 ]]; then
    echo "usage: $0 <solution.cpp> <brute.cpp> <generator.py> [iterations]" >&2
    exit 2
fi

sol_src=$1
brute_src=$2
gen=$3
iterations=${4:-500}

root=$(cd "$(dirname "$0")/../.." && pwd)
cxx=${CXX:-g++}
cxxflags=()
while IFS= read -r flag; do cxxflags+=("$flag"); done < <("$root/tools/cxxflags.sh")

work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT

"$cxx" "${cxxflags[@]}" "$sol_src" -o "$work/sol"
"$cxx" "${cxxflags[@]}" "$brute_src" -o "$work/brute"

for ((i = 1; i <= iterations; i++)); do
    python3 "$gen" "$i" > "$work/input"
    "$work/sol" < "$work/input" > "$work/sol.out"
    "$work/brute" < "$work/input" > "$work/brute.out"
    if ! diff -wq "$work/sol.out" "$work/brute.out" > /dev/null; then
        echo "MISMATCH on iteration $i"
        echo "--- input ---";    cat "$work/input"
        echo "--- solution ---"; cat "$work/sol.out"
        echo "--- brute ---";    cat "$work/brute.out"
        exit 1
    fi
done

echo "OK: $iterations random tests agree"
