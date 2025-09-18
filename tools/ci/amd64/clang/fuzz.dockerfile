FROM archlinux:base-devel

RUN pacman -Syyu --noconfirm && \
    pacman -S --noconfirm \
    bash \
    base-devel \
    clang \
    llvm \
    libc++ \
    cmake \
    git \
    python \
    python-pip \
    mesa \
    mold \
    ninja \
    zlib \
    libc++ \
    libinput \
    xorg-server-xvfb \
    libx11 \
    libxrandr \
    libxinerama \
    libxcursor \
    libxi \
    afl++ \
    afl-utils

RUN pip install --no-cache-dir --break-system-packages conan gitpython \
    && conan profile detect

RUN clang --version  \
    && conan --version \
    && pip --version \
    && cmake --version \
    && g++ --version \
    && clang --version \
    && ninja --version \
    && mold --version \
    && afl-fuzz --version \
    && afl-clang-lto --version \
    && afl-clang-lto++ --version

RUN git clone 'https://git.light7734.com/light7734/light.git' --depth=1 \
    && cd light \
    && export CC=$(which afl-clang-lto) \
    && export CXX=$(which afl-clang-lto++) \
    && export AR=$(which llvm-ar) \
    && export RANLIB=$(which llvm-ranlib) \
    && export AS=$(which llvm-as) \
    && conan install . \
        -c tools.system.package_manager:mode=install \
        -c tools.cmake.cmaketoolchain:generator=Ninja \
        -c tools.build:compiler_executables='{"c": "afl-clang-lto", "cpp": "afl-clang-lto++"}' \
        -s build_type=Release \
        -s compiler=clang \
        -s compiler.version=20 \
        -s compiler.libcxx=libc++ \
        -o use_mold=True \
        --build=missing \
    && conan install . \
        -c tools.system.package_manager:mode=install \
        -c tools.cmake.cmaketoolchain:generator=Ninja \
        -c tools.build:compiler_executables='{"c": "clang", "cpp": "clang++"}' \
        -s build_type=Release \
        -s compiler=clang \
        -s compiler.version=20 \
        -s compiler.libcxx=libc++ \
        -o use_mold=True \
        -o enable_llvm_coverage=True \
        --build=missing \
    && rm -r ../light/
