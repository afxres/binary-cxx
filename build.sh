#!/bin/bash

build_dir="build"
if [ ! -e "$build_dir" ]; then
    mkdir -p "$build_dir"
fi

cd "$build_dir"
cmake -DCMAKE_BUILD_TYPE=Debug "../next/"
cmake --build .
ctest --output-on-failure
