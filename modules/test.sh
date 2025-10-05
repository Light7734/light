#!/bin/bash

find . -type f \( -name "*.cpp" -o -name "*.hpp" \) -print0 | while IFS= read -r -d '' file; do
  scope=false
  ref=false
  if grep -Eq "Scope\s*<" "$file"; then
    scope=true
    sed -i -E 's/(Scope)(\s*<)/memory::\1\2/g' "$file"
  fi
  if grep -Eq "Ref\s*<" "$file"; then
    ref=true
    sed -i -E 's/(Ref)(\s*<)/memory::\1\2/g' "$file"
  fi
  if grep -Eq "\bcreate_scope\b" "$file"; then
    scope=true
    sed -i -E 's/\b(create_scope)\b/memory::\1/g' "$file"
  fi
  if grep -Eq "\bcreate_ref\b" "$file"; then
    ref=true
    sed -i -E 's/\b(create_ref)\b/memory::\1/g' "$file"
  fi
  if $scope || $ref; then
    includes=""
    $scope && includes+="#include <memory/scope.hpp>\n"
    $ref && includes+="#include <memory/reference.hpp>\n"
    tmp=$(mktemp)
    if [[ "$file" =~ \.hpp$ ]] && pragma_line=$(grep -En -m1 '^#pragma once' "$file" | cut -d: -f1); then
      insert_line=$((pragma_line + 2))
    else
      insert_line=1
    fi
    head -n $((insert_line - 1)) "$file" > "$tmp"
    echo -e "$includes" >> "$tmp"
    tail -n +$insert_line "$file" >> "$tmp"
    mv "$tmp" "$file"
    clang-format -i "$file"
  fi
done
