set -e
cd $(git rev-parse --show-toplevel)

find ./modules -name '*.?pp' | while read -r file; do
echo "Checking format for $file"
if ! clang-format --dry-run --Werror "$file"; then
  echo "❌ Formatting issue detected in $file"
  exit 1
fi
done

echo "✅ All files are properly formatted"
exit 0
