#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/

has_fomatting_issues=0
for file in $(find ./modules -name '*.?pp'); do
  echo "Checking format for $file"
  if ! clang-format --dry-run --Werror "$file"; then
    echo "❌ Formatting issue detected in $file"
    has_fomatting_issues=1
  fi
done

if [ "$has_fomatting_issues" -eq 0 ]; then
  echo "✅ All files are properly formatted! Well done! ^~^"
fi

exit ${has_fomatting_issues}
