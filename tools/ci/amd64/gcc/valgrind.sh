#!/bin/bash

export DEBUGINFOD_URLS="https://debuginfod.archlinux.org/"

set -e
cd $(git rev-parse --show-toplevel)/
rm -rf ./build

Xvfb :99 -screen 0 1024x768x16 &
export DISPLAY=:99

conan build . \
  -c tools.system.package_manager:mode=install \
  -c tools.cmake.cmaketoolchain:generator=Ninja \
  -s build_type=Release \
  -o enable_unit_tests=True \
  -o use_mold=True \
  --build=missing


for test in $(find ./build -type f -name '*_tests' -executable); do
  echo "Running $test"

  valgrind \
      --leak-check=full \
      --show-leak-kinds=all \
      --track-origins=yes \
      --verbose \
      --error-exitcode=255  \
      ${test} || exit 1
done
