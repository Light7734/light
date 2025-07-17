#!/bin/bash

set -e

IMAGE_DIR="$(git rev-parse --show-toplevel)/tools/ci/images"

cd "$IMAGE_DIR/clang_format"
docker build -t clang_format .

cd "$IMAGE_DIR/static_analysis"
docker build -t static_analysis .

cd "$IMAGE_DIR/unit_tests"
docker build -t unit_tests .

cd "$IMAGE_DIR/valgrind"
docker build -t valgrind .

echo "WOOOOOOOOOOOOOOOOH!!! DONE :D"
