#!/bin/bash
#
# Build and run the test suite for one or more target architectures.
#
#   bash scripts/test-multiarch.sh                       # host only
#   bash scripts/test-multiarch.sh x86_64 aarch64 armhf s390x
#   bash scripts/test-multiarch.sh --all                 # every known target,
#                                                        # skipping missing ones
#   bash scripts/test-multiarch.sh --clean s390x         # reconfigure from scratch
#
# Covered widths: 64-bit little endian (x86_64, aarch64, riscv64), 32-bit little
# endian (i686, armhf), 64-bit big endian (ppc64, s390x), 32-bit big endian
# (mips). Add a target by adding one line to `arch_info`.
#
# Every target is configured in build-tests-<arch>/ through a generated
# toolchain file, so CMake treats it as a cross build and CTest runs the
# binaries through qemu-user with the matching sysroot; binfmt_misc is not
# required. The ELF header of the resulting test binary is checked against the
# requested width and endianness, so a mislabelled toolchain cannot pass as a
# successful target.
#
# Toolchains, e.g. for s390x (repeat per target):
#   sudo apt install gcc-s390x-linux-gnu g++-s390x-linux-gnu \
#                    libboost-test-dev:s390x qemu-user
#
# Environment: BUILD_TYPE (default Debug, which is what enables the tests),
# JOBS (default: online CPUs), BUILD_ROOT (default: repository root).

set -uo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SOURCE_DIR="$PROJECT_ROOT/code"
BUILD_ROOT="${BUILD_ROOT:-$PROJECT_ROOT}"
BUILD_TYPE="${BUILD_TYPE:-Debug}"
JOBS="${JOBS:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)}"

ALL_TARGETS="x86_64 i686 aarch64 armhf riscv64 ppc64 mips s390x"
CLEAN=0
ALLOW_MISSING=0
SKIPPED=0

usage() {
    sed -n '2,27p' "${BASH_SOURCE[0]}" | sed -e 's/^# \{0,1\}//'
}

# Sets ARCH TRIPLE QEMU DEBARCH BITS ENDIAN for a target name or alias.
arch_info() {
    case "$1" in
        x86_64 | amd64 | x64) ARCH=x86_64 TRIPLE=x86_64-linux-gnu QEMU=qemu-x86_64 DEBARCH=amd64 BITS=64 ENDIAN=little ;;
        i686 | i386 | x86) ARCH=i686 TRIPLE=i686-linux-gnu QEMU=qemu-i386 DEBARCH=i386 BITS=32 ENDIAN=little ;;
        aarch64 | arm64) ARCH=aarch64 TRIPLE=aarch64-linux-gnu QEMU=qemu-aarch64 DEBARCH=arm64 BITS=64 ENDIAN=little ;;
        armhf | armv7l | armv7) ARCH=armhf TRIPLE=arm-linux-gnueabihf QEMU=qemu-arm DEBARCH=armhf BITS=32 ENDIAN=little ;;
        riscv64) ARCH=riscv64 TRIPLE=riscv64-linux-gnu QEMU=qemu-riscv64 DEBARCH=riscv64 BITS=64 ENDIAN=little ;;
        ppc64 | powerpc64) ARCH=ppc64 TRIPLE=powerpc64-linux-gnu QEMU=qemu-ppc64 DEBARCH=ppc64 BITS=64 ENDIAN=big ;;
        mips) ARCH=mips TRIPLE=mips-linux-gnu QEMU=qemu-mips DEBARCH=mips BITS=32 ENDIAN=big ;;
        s390x) ARCH=s390x TRIPLE=s390x-linux-gnu QEMU=qemu-s390x DEBARCH=s390x BITS=64 ENDIAN=big ;;
        *) return 1 ;;
    esac
}

HOST_ARCH="$(uname -m)"
arch_info "$HOST_ARCH" >/dev/null 2>&1 && HOST_ARCH="$ARCH"

report_arch=()
report_bits=()
report_endian=()
report_tests=()
report_status=()
report_note=()

record() {
    report_arch+=("$1")
    report_bits+=("$2")
    report_endian+=("$3")
    report_tests+=("$4")
    report_status+=("$5")
    report_note+=("$6")
}

show_tail() {
    [ -s "$1" ] || return 0
    tail -n 20 "$1" | sed -e 's/^/    | /'
}

run_target() {
    local requested="$1"
    if ! arch_info "$requested"; then
        echo "error: unknown target '$requested'"
        record "$requested" "-" "-" "-" "error" "unknown target"
        FAILED=1
        return
    fi

    local native=0
    [ "$ARCH" = "$HOST_ARCH" ] && native=1
    local build_dir="$BUILD_ROOT/build-tests-$ARCH"
    local label="$ARCH $TRIPLE $BITS-bit $ENDIAN endian"

    if [ "$native" -eq 0 ]; then
        local missing=()
        [ -x "/usr/bin/$TRIPLE-gcc" ] || missing+=("gcc-$TRIPLE")
        [ -x "/usr/bin/$TRIPLE-g++" ] || missing+=("g++-$TRIPLE")
        [ -d "/usr/$TRIPLE" ] || missing+=("libc6-dev-$DEBARCH-cross")
        command -v "$QEMU" >/dev/null 2>&1 || missing+=("qemu-user")
        if [ "${#missing[@]}" -gt 0 ]; then
            local hint="missing ${missing[*]}"
            if [ "$ALLOW_MISSING" -eq 1 ]; then
                printf 'skip  %s\n      %s\n' "$label" "$hint"
                record "$ARCH" "$BITS" "$ENDIAN" "-" "skip" "$hint"
                SKIPPED=$((SKIPPED + 1))
            else
                printf 'error %s\n      %s (--allow-missing to skip)\n' "$label" "$hint"
                record "$ARCH" "$BITS" "$ENDIAN" "-" "error" "$hint"
                FAILED=1
            fi
            return
        fi
    fi

    printf 'build %s\n' "$label"
    local signature="arch=$ARCH triple=$TRIPLE build_type=$BUILD_TYPE native=$native"
    if [ "$CLEAN" -eq 1 ]; then
        rm -rf "$build_dir"
    elif [ -f "$build_dir/CMakeCache.txt" ]; then
        local previous=""
        [ -f "$build_dir/.multiarch-signature" ] && previous="$(cat "$build_dir/.multiarch-signature")"
        if [ "$previous" != "$signature" ]; then
            echo "  build directory was configured differently, reconfiguring"
            rm -rf "$build_dir"
        fi
    fi
    mkdir -p "$build_dir"
    printf '%s\n' "$signature" >"$build_dir/.multiarch-signature"

    local cmake_args=(-S "$SOURCE_DIR" -B "$build_dir"
        -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
        -DBINARY_BUILD_TESTS=ON)
    if [ "$native" -eq 0 ]; then
        local toolchain="$build_dir/toolchain.cmake"
        {
            echo "set(CMAKE_SYSTEM_NAME Linux)"
            echo "set(CMAKE_SYSTEM_PROCESSOR $ARCH)"
            echo "set(CMAKE_C_COMPILER /usr/bin/$TRIPLE-gcc)"
            echo "set(CMAKE_CXX_COMPILER /usr/bin/$TRIPLE-g++)"
            echo "set(CMAKE_CROSSCOMPILING_EMULATOR $QEMU -L /usr/$TRIPLE)"
        } >"$toolchain"
        cmake_args+=(-DCMAKE_TOOLCHAIN_FILE="$toolchain")
    fi

    if ! cmake "${cmake_args[@]}" >"$build_dir/configure.log" 2>&1; then
        echo "  configure failed"
        show_tail "$build_dir/configure.log"
        record "$ARCH" "$BITS" "$ENDIAN" "-" "error" "configure failed"
        FAILED=1
        return
    fi

    if ! cmake --build "$build_dir" --parallel "$JOBS" >"$build_dir/build.log" 2>&1; then
        echo "  build failed"
        grep -E "error:|Error " "$build_dir/build.log" | head -n 10 | sed -e 's/^/    | /'
        record "$ARCH" "$BITS" "$ENDIAN" "-" "error" "build failed"
        FAILED=1
        return
    fi

    local test_log="$build_dir/tests.log"
    if ! ctest --test-dir "$build_dir" --output-on-failure >"$test_log" 2>&1; then
        echo "  tests failed"
        show_tail "$test_log"
        record "$ARCH" "$BITS" "$ENDIAN" "-" "error" "tests failed"
        FAILED=1
        return
    fi
    local tests
    tests="$(sed -nE 's/^[0-9]+% tests passed, [0-9]+ tests failed out of ([0-9]+)$/\1 passed/p' "$test_log" |
        tail -n 1)"
    tests="${tests:-passed}"

    local elf="" status="ok" note=""
    local test_binary="$build_dir/binary-tests/binary-tests"
    if [ ! -f "$test_binary" ]; then
        status="error" note="test binary missing"
    elif ! command -v file >/dev/null 2>&1; then
        note="file not installed, ELF unchecked"
    else
        elf="$(file -b "$test_binary")"
        case "$elf" in
            *"ELF $BITS-bit LSB"*) [ "$ENDIAN" = little ] || { status="bad-elf" note="ELF reports LSB"; } ;;
            *"ELF $BITS-bit MSB"*) [ "$ENDIAN" = big ] || { status="bad-elf" note="ELF reports MSB"; } ;;
            *) status="bad-elf" note="not $BITS-bit" ;;
        esac
    fi
    [ "$status" = "ok" ] || FAILED=1
    printf '  tests: %s, elf: %s %s\n' "$tests" "$BITS-bit" "$ENDIAN"
    record "$ARCH" "$BITS" "$ENDIAN" "$tests" "$status" "$note"
}

TARGETS=()
while [ $# -gt 0 ]; do
    case "$1" in
        -c | --clean) CLEAN=1 ;;
        -a | --all)
            read -r -a TARGETS <<<"$ALL_TARGETS"
            ALLOW_MISSING=1
            ;;
        --allow-missing) ALLOW_MISSING=1 ;;
        -j | --jobs)
            shift
            JOBS="${1:-$JOBS}"
            ;;
        -j*) JOBS="${1#-j}" ;;
        -h | --help)
            usage
            exit 0
            ;;
        --)
            shift
            TARGETS+=("$@")
            break
            ;;
        -*)
            echo "error: unknown option '$1'" >&2
            usage >&2
            exit 2
            ;;
        *) TARGETS+=("$1") ;;
    esac
    shift
done

[ "${#TARGETS[@]}" -gt 0 ] || TARGETS=("$HOST_ARCH")

FAILED=0
for target in "${TARGETS[@]}"; do
    run_target "$target"
done

printf '\n%-8s %-4s %-8s %-10s %-8s %s\n' "target" "bits" "endian" "tests" "status" "note"
for i in "${!report_arch[@]}"; do
    printf '%-8s %-4s %-8s %-10s %-8s %s\n' \
        "${report_arch[$i]}" "${report_bits[$i]}" "${report_endian[$i]}" \
        "${report_tests[$i]}" "${report_status[$i]}" "${report_note[$i]}"
done

if [ "$FAILED" -ne 0 ]; then
    printf '\n%s\n' "one or more targets failed"
    exit 1
fi
if [ "$SKIPPED" -ne 0 ]; then
    printf '\n%s\n' "all targets passed, $SKIPPED skipped"
else
    printf '\n%s\n' "all targets passed"
fi
