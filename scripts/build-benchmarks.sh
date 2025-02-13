#!/bin/bash

PROJECT_ROOT="$PWD"
PROJECT_DIR="$PROJECT_ROOT/next"
BUILD_DIR="$PROJECT_ROOT/build-benchmarks"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake -DCMAKE_BUILD_TYPE=Release -DBINARY_BUILD_BENCHMARKS=ON "$PROJECT_DIR"
cmake --build . --parallel
