#!/bin/bash
#
# Build the benchmarks, then run one of them.
#
#   bash scripts/run-benchmark.sh                  # the integration benchmark
#   bash scripts/run-benchmark.sh named            # whatever binary matches "named"
#   bash scripts/run-benchmark.sh integration --benchmark_filter=Encode
#
# The build is incremental, so calling this before every run costs nothing once
# the tree is up to date. Build output goes to stderr on purpose: stdout belongs
# to the benchmark, so `scripts/run-benchmark-report.sh` can pipe it into JSON.
#
# Environment: JOBS (default: online CPUs).

set -uo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build-benchmarks"
JOBS="${JOBS:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)}"

BENCHMARK_NAME="integration"
if [ $# -gt 0 ]; then
    BENCHMARK_NAME="$1"
    shift
fi

cmake -S "$PROJECT_ROOT/code" -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE=Release -DBINARY_BUILD_BENCHMARKS=ON >&2 || exit 1
cmake --build "$BUILD_DIR" --parallel "$JOBS" >&2 || exit 1

mapfile -t executables < <(
    find "$BUILD_DIR" -type f -perm -u+x -path "*$BENCHMARK_NAME*" | sort
)
if [ "${#executables[@]}" -ne 1 ]; then
    printf 'no benchmark or multiple benchmarks match "%s"\n' "$BENCHMARK_NAME" >&2
    if [ "${#executables[@]}" -gt 0 ]; then
        printf '  %s\n' "${executables[@]}" >&2
    fi
    exit 1
fi

exec "${executables[0]}" "$@"
