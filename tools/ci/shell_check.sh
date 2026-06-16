#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"

has_shellcheck_issues=0
while IFS= read -r -d '' file; do
    echo "Checking shell script $file"

    if ! shellcheck "$file"; then
        echo "❌ Shellcheck issue detected in $file"
        has_shellcheck_issues=1
    fi
done < <(find ./modules ./tools -name '*.sh' -print0)

if [ "$has_shellcheck_issues" -eq 0 ]; then
    echo "✅ All files are properly shellchecked! Well done! ^~^"
fi
exit ${has_shellcheck_issues}
