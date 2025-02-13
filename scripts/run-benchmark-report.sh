#!/bin/bash

PROJECT_ROOT="$PWD"
PROJECT_RESULT_DIR="$PROJECT_ROOT/build-result"
BENCHMARK_RESULT_FILE_PATH="$PROJECT_RESULT_DIR/benchmark-result.json"
BENCHMARK_EXE="$PROJECT_ROOT/build-benchmarks/binary-benchmarks/integration-tests/binary-benchmarks-integration-tests"

if [ ! -f "$BENCHMARK_EXE" ]; then
    echo "benchmark not found"
    exit 1
fi

mkdir -p "$PROJECT_RESULT_DIR"
"$BENCHMARK_EXE" --benchmark_format=json | tee "$BENCHMARK_RESULT_FILE_PATH"
