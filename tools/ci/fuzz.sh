#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"
rm -rf ./build/

XDG_RUNTIME_DIR='/run/user/1000'
export XDG_RUNTIME_DIR

#!/bin/bash

set -euo pipefail
cd "$(git rev-parse --show-toplevel)/"
# rm -rf ./build/

XDG_RUNTIME_DIR='/run/user/1000'
export XDG_RUNTIME_DIR

export AR=llvm-ar
export RANLIB=llvm-ranlib
export AS=llvm-as
export LD=afl-clang-lto

LD=afl-clang-lto cmake \
    -S . \
    -B build \
    -G Ninja \
    -D CMAKE_C_COMPILER="$(which afl-clang-lto)" \
    -D CMAKE_CXX_COMPILER="$(which afl-clang-lto++)" \
    -D CMAKE_CXX_FLAGS="-std=c++26 -stdlib=libc++ -fsanitize=fuzzer" \
    -D CMAKE_EXPORT_COMPILE_COMMANDS=TRUE \
    -D ENABLE_FUZZ_TESTS=ON \
    -D CMAKE_LINKER="$(which afl-clang-lto)" \
    -D CMAKE_BUILD_TYPE=Release

LD=afl-clang-lto cmake --build ./build -j"$(nproc)"
