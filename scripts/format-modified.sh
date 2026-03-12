#!/usr/bin/env bash
# Run clang-format only on source files that are modified (staged or unstaged) vs HEAD.

set -e
cd "$(dirname "$0")/.."

if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  echo "Not a git repository; formatting all source files."
  find src -type f \( -name '*.cpp' -o -name '*.c' -o -name '*.h' \) -exec clang-format -i {} +
  exit 0
fi

# Paths of .cpp, .c, .h under src/ that differ from HEAD (modified/staged)
modified=$(git diff --name-only --diff-filter=ACMR HEAD -- src/ 2>/dev/null | grep -E '\.(cpp|c|h)$' || true)
# Untracked (new) source files under src/
untracked=$(git ls-files --others --exclude-standard -- src/ 2>/dev/null | grep -E '\.(cpp|c|h)$' || true)
# Merge and deduplicate
files=$(echo "$modified" "$untracked" | tr ' \n' '\n' | sort -u | sed '/^$/d')

if [ -z "$files" ]; then
  echo "No modified or untracked source files to format."
  exit 0
fi

count=$(echo "$files" | wc -l)
echo "Formatting ${count} file(s) ..."
echo "$files" | xargs clang-format -i
