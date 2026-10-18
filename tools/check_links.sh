#!/usr/bin/env bash
# Check every https:// link in the Markdown files. Codeforces and the Australian
# Maths Trust block scripted requests (HTTP 403); verify those in a browser.
set -uo pipefail

root=$(cd "$(dirname "$0")/.." && pwd)
failed=0
# The course's own repository may be private (404 to anonymous requests): skip it.
own_repo=$(git -C "$root" remote get-url origin 2> /dev/null | sed 's/\.git$//')
while IFS= read -r url; do
    if [[ -n $own_repo && $url == "$own_repo"* ]]; then continue; fi
    code=$(curl -s -o /dev/null -L -m 20 -A 'Mozilla/5.0' -w '%{http_code}' "$url")
    if [[ $code != 200 ]]; then
        echo "$code $url"
        [[ $code == 403 && $url =~ (codeforces\.com|amt\.edu\.au) ]] || failed=1
    fi
done < <(grep -rhoE 'https://[^ )|`>"]+' --include='*.md' "$root" | sed 's/[.,]$//' | sort -u)

if [[ $failed == 0 ]]; then echo "links OK"; fi
exit $failed
