#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

dirs=($REPO_ROOT/src $REPO_ROOT/tests)

for file in $(find "${dirs[@]}" -type f \( -name '*.cpp' -o -name '*.h' \)); do
  clang-format -i "$file"
  echo "Formatted $file"
done

echo "All files have been formatted."
