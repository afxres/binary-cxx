#!/bin/bash
#
# Write the integration benchmark as JSON, for benchmark comparison tooling.
#
#   bash scripts/run-benchmark-report.sh
#
# Building and locating the binary is `run-benchmark.sh`'s job, so this script
# only picks the output format and the destination file.

set -uo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
RESULT_DIR="$PROJECT_ROOT/build-result"
RESULT_FILE="$RESULT_DIR/benchmark-result.json"

mkdir -p "$RESULT_DIR"
bash "$PROJECT_ROOT/scripts/run-benchmark.sh" integration --benchmark_format=json |
    tee "$RESULT_FILE"
