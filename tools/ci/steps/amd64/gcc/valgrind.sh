#!/bin/bash

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build

conan build . \
  -c tools.system.package_manager:mode=install \
  -c tools.cmake.cmaketoolchain:generator=Ninja \
  -s build_type=Release \
  -o enable_tests=True \
  -o use_mold=True \
  --build=missing

find ./build -type f -name "*_tests" -executable | xargs -I {} bash -c 'valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=255 {}' || exit 1
