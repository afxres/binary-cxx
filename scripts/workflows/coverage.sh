#!/bin/bash

BUILD_DIR="build"
COVERAGE_DIR="coverage"
COVERAGE_FILE_PATH="$COVERAGE_DIR/lcov.info"
mkdir -p "$COVERAGE_DIR"
lcov --capture --ignore-errors mismatch --directory "$BUILD_DIR" --output-file "$COVERAGE_FILE_PATH"
lcov --remove "$COVERAGE_FILE_PATH" '/usr/*' --output-file "$COVERAGE_FILE_PATH"
lcov --remove "$COVERAGE_FILE_PATH" '*/binary-tests/*' --output-file "$COVERAGE_FILE_PATH"
