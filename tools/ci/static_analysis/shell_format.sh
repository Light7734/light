#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"

has_fomatting_issues=0

while IFS= read -r -d '' file; do
    echo "Checking format for $file"

    if ! shfmt -i 4 -ci -d "$file"; then
        echo "❌ Formatting issue detected in $file"
        has_fomatting_issues=1
    fi
done < <(find ./modules ./tools -name '*.sh' -print0)

if [ "$has_fomatting_issues" -eq 0 ]; then
    echo "✅ All files are properly formatted! Well done! ^~^"
fi

exit ${has_fomatting_issues}
