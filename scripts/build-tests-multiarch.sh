#!/bin/bash

PROJECT_ROOT="$PWD"
PROJECT_DIR="$PROJECT_ROOT/code"

build_tests() {
    local arch="$1"
    case "$arch" in
    "armhf")
        local cc="/usr/bin/arm-linux-gnueabihf-gcc"
        local cx="/usr/bin/arm-linux-gnueabihf-g++"
        ;;
    *)
        local cc="/usr/bin/$arch-linux-gnu-gcc"
        local cx="/usr/bin/$arch-linux-gnu-g++"
        ;;
    esac
    if [ ! -f "$cc" ] || [ ! -f "$cx" ]; then
        echo "error: missing compiler for '$arch'"
        return
    fi

    local build_dir="$PROJECT_ROOT/build-tests-multiarch-$arch"
    mkdir -p "$build_dir"
    cd "$build_dir"
    cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER="$cc" -DCMAKE_CXX_COMPILER="$cx" -DBINARY_BUILD_TESTS=ON "$PROJECT_DIR"
    cmake --build . --parallel
    ctest --output-on-failure
}

for i in "$@"; do
    build_tests "$i"
done
