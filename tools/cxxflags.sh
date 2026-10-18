#!/usr/bin/env bash
# Print the compiler flags used for every solution in this repo.
# Works around two common macOS problems:
#   1. Apple clang has no <bits/stdc++.h>  -> use templates/include fallback.
#   2. A Command Line Tools install whose clang cannot find the C++ standard
#      headers ('algorithm' file not found) -> point it at the SDK's libc++.
set -euo pipefail

root=$(cd "$(dirname "$0")/.." && pwd)
cxx=${CXX:-g++}
flags=(-std=c++17 -O2 -Wall -Wextra -I "$root/templates/include")

if ! printf '#include <vector>\nint main(){}\n' |
        "$cxx" -std=c++17 -x c++ -fsyntax-only - 2> /dev/null; then
    if command -v xcrun > /dev/null; then
        flags+=(-isystem "$(xcrun --show-sdk-path)/usr/include/c++/v1")
    fi
fi

printf "%s\n" "${flags[@]}"
