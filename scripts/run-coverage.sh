#!/bin/bash

PROJECT_ROOT="$PWD"
PROJECT_RESULT_DIR="$PROJECT_ROOT/build-result"
COVERAGE_FILE_PATH="$PROJECT_RESULT_DIR/lcov.info"

mkdir -p "$PROJECT_RESULT_DIR"
lcov --capture --ignore-errors mismatch,inconsistent --directory . --no-external --exclude '*/binary-tests/*' --output-file "$COVERAGE_FILE_PATH"
