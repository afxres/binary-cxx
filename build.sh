#!/bin/bash

build_dir="build"
if [ ! -e "$build_dir" ]; then
    mkdir -p "$build_dir"
fi

cd "$build_dir"
cmake "../next/"
cmake --build . --config Debug
ctest --output-on-failure
