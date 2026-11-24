#!/bin/bash
#
# Collect the gcov data of an instrumented Debug build into build-result/lcov.info.
#
#   bash scripts/run-coverage.sh
#
# Run the tests first: the instrumented binaries write their .gcda files while
# they run, and this script only converts what is already on disk.
#
# Requires lcov: apt install lcov.

set -euo pipefail

cd "$(dirname "${BASH_SOURCE[0]}")/.." || exit 1

PROJECT_ROOT="$PWD"
PROJECT_RESULT_DIR="$PROJECT_ROOT/build-result"
COVERAGE_FILE_PATH="$PROJECT_RESULT_DIR/lcov.info"

if ! command -v lcov >/dev/null 2>&1; then
    echo "lcov not installed: apt install lcov" >&2
    exit 1
fi

mkdir -p "$PROJECT_RESULT_DIR"
lcov --capture --ignore-errors mismatch,inconsistent,range --directory . --no-external --exclude '*-tests/*' --output-file "$COVERAGE_FILE_PATH"
