#!/bin/bash

# Find all .cpp and .h files
dirs=(../src ../lib)
files=$(find "${dirs[@]}" -type f \( -name '*.cpp' -o -name '*.h' \))

format_issues_found=0
for file in $files; do
  if ! diff -q <(clang-format "$file") "$file" >/dev/null; then
    echo "Formatting issue found in: $file"
    format_issues_found=1
  fi
done

if [ $format_issues_found ]; then
  echo "ERROR: Some files are not properly formatted. Please run clang-format."
  exit 1
else
  echo "All files are properly formatted."
  exit 0
fi