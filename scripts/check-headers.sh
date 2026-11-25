#!/bin/bash
#
# Compile every public header on its own, the way an editor sees it.
#
#   bash scripts/check-headers.sh
#
# A header that relies on another one being included first still builds through
# any translation unit that happens to include both, so the compiler never
# complains while an editor's per-file analysis does: clangd reports the missing
# name in the header itself. Compiling each header as its own translation unit
# catches the same defect without an editor.
#
# Only headers under an `include` directory are checked: they are the ones a
# consumer can include first.

set -uo pipefail

cd "$(dirname "${BASH_SOURCE[0]}")/.." || exit 1

INCLUDES=(-Icode/binary/include -Icode/binary-experimental/include)

mapfile -t headers < <(find code -path '*/include/*' -type f -name '*.hpp' | sort)
if [ "${#headers[@]}" -eq 0 ]; then
    echo "no headers found under code/*/include/" >&2
    exit 1
fi

compilers=()
for candidate in g++ clang++; do
    if command -v "$candidate" >/dev/null 2>&1; then
        compilers+=("$candidate")
    fi
done
if [ "${#compilers[@]}" -eq 0 ]; then
    echo "no C++ compiler found: apt install g++ clang" >&2
    exit 1
fi

printf '%s headers\n' "${#headers[@]}"
for compiler in "${compilers[@]}"; do
    printf '  %s\n' "$("$compiler" --version | head -1)"
done

failed=0
for header in "${headers[@]}"; do
    for compiler in "${compilers[@]}"; do
        if ! "$compiler" -std=c++20 -fsyntax-only "${INCLUDES[@]}" -x c++-header "$header" 2>/tmp/check-headers.$$; then
            echo "not self-contained: $header ($compiler)" >&2
            sed -n '1,12p' /tmp/check-headers.$$ | sed 's/^/    /' >&2
            failed=1
        fi
    done
done
rm -f /tmp/check-headers.$$

if [ "$failed" -ne 0 ]; then
    exit 1
fi

echo "all headers compile on their own"
