#!/bin/bash

PROJECT_ROOT="$PWD"
PROJECT_DIR="$PROJECT_ROOT/next"
BUILD_DIR="$PWD/build"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake -DCMAKE_BUILD_TYPE=Debug "$PROJECT_DIR"
cmake --build . --parallel
ctest --output-on-failure
