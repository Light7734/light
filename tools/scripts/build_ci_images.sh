#!/bin/bash

set -e
CI_DIR="$(git rev-parse --show-toplevel)/tools/ci/"

echo "===========[ amd64_clang ]==========="]
echo "==> Building amd64_clang_coverage..."
docker build -t amd64_clang_coverage -f $CI_DIR/amd64/clang/coverage.dockerfile .
echo "...DONE <=="

echo "==> Building amd64_clang_lsan..."
docker build -t amd64_clang_lsan -f $CI_DIR/amd64/clang/lsan.dockerfile .
echo "...DONE <=="

echo "==> Building image: amd64_clang_msan"
docker build -t amd64_clang_msan -f $CI_DIR/amd64/clang/msan.dockerfile .
echo "...DONE <=="

echo "==> Building image: clang_format"
docker build -t clang_format -f $CI_DIR/static_analysis/clang_format.dockerfile .
echo "...DONE <=="

echo "==> Building image: static_analysis"
docker build -t clang_tidy -f $CI_DIR/static_analysis/clang_tidy.dockerfile .
echo "...DONE <=="

echo "===========[ amd64_gcc ]==========="]
echo "==> Building image: amd64_gcc_unit_tests"
docker build -t amd64_gcc_unit_tests -f $CI_DIR/amd64/gcc/unit_tests.dockerfile .
echo "...DONE <=="

echo "==> Building image: amd64_gcc_valgrind"
docker build -t amd64_gcc_valgrind -f $CI_DIR/amd64/gcc/valgrind.dockerfile .
echo "...DONE <=="

echo "WOOOOOOOOOOOOOOOOH!!! DONE :D"
