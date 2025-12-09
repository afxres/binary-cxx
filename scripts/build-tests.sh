#!/bin/bash

"$(cd "$(dirname "$0")" && pwd)/build-tests-multiarch.sh" "$(uname -m)"
