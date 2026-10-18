#!/usr/bin/env bash
# Check every https:// link in the Markdown files. Codeforces and the Australian
# Maths Trust block scripted requests (HTTP 403); verify those in a browser.
set -uo pipefail

root=$(cd "$(dirname "$0")/.." && pwd)
failed=0
while IFS= read -r url; do
    code=$(curl -s -o /dev/null -L -m 20 -A 'Mozilla/5.0' -w '%{http_code}' "$url")
    if [[ $code != 200 ]]; then
        echo "$code $url"
        [[ $code == 403 && $url =~ (codeforces\.com|amt\.edu\.au) ]] || failed=1
    fi
done < <(grep -rhoE 'https://[^ )|`>"]+' --include='*.md' "$root" | sed 's/[.,]$//' | sort -u)

if [[ $failed == 0 ]]; then echo "links OK"; fi
exit $failed
