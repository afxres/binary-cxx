#!/bin/bash

PROJECT_ROOT="$PWD"
PROJECT_DIR="$PROJECT_ROOT/code"
BUILD_DIR="$PROJECT_ROOT/build-tests"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake -DCMAKE_BUILD_TYPE=Debug -DBINARY_BUILD_TESTS=ON "$PROJECT_DIR"
cmake --build . --parallel
ctest --output-on-failure
