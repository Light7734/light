#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"

has_fomatting_issues=0
while IFS= read -r -d '' file; do
    echo "Checking format for $file"

    if ! clang-format --dry-run --Werror "$file"; then
        echo "❌ Formatting issue detected in $file"
        has_fomatting_issues=1
    fi
done < <(find ./modules -name '*.?pp' -print0)

if [ "$has_fomatting_issues" -eq 0 ]; then
    echo "✅ All files are properly formatted! Well done! ^~^"
fi
exit ${has_fomatting_issues}
