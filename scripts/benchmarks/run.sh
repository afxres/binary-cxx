#!/bin/bash

BUILD_DIR_NAME="build-benchmarks"
BENCHMARK_NAME="$1"

if [ -z "$BENCHMARK_NAME" ]; then
    BENCHMARK_NAME="integration"
fi

EXECUTABLE_FILE=$(find . -type f | grep "$BUILD_DIR_NAME.*$BENCHMARK_NAME" | xargs --no-run-if-empty file | grep "ELF.*executable" | awk -F ':' '{print $1}')
if [ -z "$EXECUTABLE_FILE" ] || [ "$(echo "$EXECUTABLE_FILE" | wc -l)" -ne "1" ]; then
    echo "no benchmark or multiple benchmarks found"
    exit 1
fi

"$EXECUTABLE_FILE"
