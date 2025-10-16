#!/usr/bin/env bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"

has_formatting_issues=0
while IFS= read -r -d '' file; do
    echo "Checking format for $file"

    if ! cmake-format --check "$file"; then
        echo "❌ Formatting issue detected in $file"
        has_formatting_issues=1
    fi
done < <(find ./modules ./tools/cmake -type f \( -name 'CMakeLists.txt' -o -name '*.cmake' \) -print0)

if [ "$has_formatting_issues" -ne 0 ]; then
    echo "✅ All files are properly formatted! Well done! ^~^"
fi
exit ${has_formatting_issues}
