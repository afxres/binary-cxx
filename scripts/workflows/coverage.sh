#!/bin/bash

PROJECT_ROOT="$PWD"
COVERAGE_DIR="$PROJECT_ROOT/coverage"
COVERAGE_FILE_PATH="$COVERAGE_DIR/lcov.info"
mkdir -p "$COVERAGE_DIR"
lcov --capture --ignore-errors mismatch,inconsistent --directory . --no-external --exclude '*/binary-tests/*' --output-file "$COVERAGE_FILE_PATH"
