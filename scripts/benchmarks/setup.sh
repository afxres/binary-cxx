#!/bin/bash

PROJECT_ROOT="$PWD"
DEPENDENCIES_DIR="$PROJECT_ROOT/dependencies"
GOOGLE_BENCHMARK_DIR="$DEPENDENCIES_DIR/benchmark"
GOOGLE_BENCHMARK_BUILD_DIR="$GOOGLE_BENCHMARK_DIR/build"

if [ ! -d "$GOOGLE_BENCHMARK_DIR" ]; then
    mkdir -p "$DEPENDENCIES_DIR"
    cd "$DEPENDENCIES_DIR"
    git clone https://github.com/google/benchmark.git
fi

cd "$GOOGLE_BENCHMARK_DIR"
if [ ! -d "$GOOGLE_BENCHMARK_BUILD_DIR" ]; then
    mkdir -p "$GOOGLE_BENCHMARK_BUILD_DIR"
fi

cd "$GOOGLE_BENCHMARK_BUILD_DIR"
cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release "$GOOGLE_BENCHMARK_DIR"
cmake --build . --config Release
