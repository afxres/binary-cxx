#!/bin/bash
#
# Check the formatting of the C++ sources under code/.
#
#   bash scripts/check-format.sh          # report, exit 1 on any finding
#   bash scripts/check-format.sh --fix    # rewrite the files with clang-format
#
# The style is declared once in .clang-format. clang-format's output is not
# stable across major versions: a newer binary may reformat a file the older one
# accepted. The check therefore prints the version it used, and CI reports its
# result instead of gating on it, so a runner image bump cannot turn an unrelated
# change red.
#
# Requires clang-format: apt install clang-format, or pip install clang-format.

set -uo pipefail

cd "$(dirname "${BASH_SOURCE[0]}")/.." || exit 1

FIX=0
case "${1:-}" in
    --fix) FIX=1 ;;
    -h | --help)
        sed -n '2,14p' "${BASH_SOURCE[0]}" | sed -e 's/^# \{0,1\}//'
        exit 0
        ;;
    "") ;;
    *)
        echo "usage: $0 [--fix]" >&2
        exit 2
        ;;
esac

if ! command -v clang-format >/dev/null 2>&1; then
    echo "clang-format not installed: apt install clang-format" >&2
    exit 1
fi

mapfile -t files < <(find code -type f \( -name '*.hpp' -o -name '*.cpp' \) | sort)
if [ "${#files[@]}" -eq 0 ]; then
    echo "no C++ sources found under code/" >&2
    exit 1
fi

printf '%s, %s files\n' "$(clang-format --version)" "${#files[@]}"

if [ "$FIX" -eq 1 ]; then
    clang-format -i --style=file "${files[@]}"
    exit 0
fi

if clang-format --dry-run --Werror --style=file "${files[@]}"; then
    echo "all files properly formatted"
    exit 0
fi

echo "run '$0 --fix' to reformat" >&2
exit 1
