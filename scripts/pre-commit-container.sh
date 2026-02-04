#!/bin/sh
set -e
cd "$(git rev-parse --show-toplevel)"

# Staged C/C++ files under src/
FILES=$(git diff --cached --name-only --diff-filter=ACM | grep -E '^src/.*\.(cpp|c|h)$' || true)
if [ -z "$FILES" ]; then
  exit 0
fi

echo "Running clang-format (dry-run) on staged files..."
if ! echo "$FILES" | xargs clang-format --dry-run -Werror 2>/dev/null; then
  echo ""
  echo "Commit blocked: some staged files need formatting. Run the fix target, then git add and commit again."
  exit 1
fi
exit 0