#!/bin/bash

dirs=(../src)

for file in $(find "${dirs[@]}" -type f \( -name '*.cpp' -o -name '*.h' \)); do
  clang-format -i "$file"
  echo "Formatted $file"
done

echo "All files have been formatted."