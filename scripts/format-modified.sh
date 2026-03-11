#!/usr/bin/env bash
# Run clang-format only on source files that are modified (staged or unstaged) vs HEAD.

set -e
cd "$(dirname "$0")/.."

if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  echo "Not a git repository; formatting all source files."
  find src -type f \( -name '*.cpp' -o -name '*.c' -o -name '*.h' \) -exec clang-format -i {} +
  exit 0
fi

# Paths of .cpp, .c, .h under src/ that differ from HEAD
files=$(git diff --name-only --diff-filter=ACMR HEAD -- src/ 2>/dev/null | grep -E '\.(cpp|c|h)$' || true)

if [ -z "$files" ]; then
  echo "No modified source files to format."
  exit 0
fi

count=$(echo "$files" | wc -l)
echo "Formatting ${count} modified file(s)..."
echo "$files" | xargs clang-format -i
