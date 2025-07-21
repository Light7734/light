FROM archlinux:latest

RUN pacman -Syu --noconfirm && \
    pacman -S --noconfirm \
    bash \
    base-devel \
    git \
    cmake \
    ninja \
    python \
    python-pip \
    clang \
    llvm \
    mesa \
    mold \
    ninja \
    curl \
    wget \
    zlib

RUN pip install --no-cache-dir --break-system-packages conan gitpython \
    && conan profile detect

RUN clang --version  \
    && pip --version \
    && conan --version \
    && cmake --version \
    && g++ --version \
    && clang --version \
    && ninja --version \
    && mold --version \
    && llvm-profdata --version \
    && llvm-cov --version

RUN git clone 'https://git.light7734.com/light7734/light.git' \
    && cd light; git checkout 'ci/code_cov' \
    && conan build . \
        -c tools.system.package_manager:mode=install \
        -c tools.cmake.cmaketoolchain:generator=Ninja \
        -c tools.build:compiler_executables='{"c": "clang", "cpp": "clang++"}' \
        -s build_type=Release \
        -s compiler=clang \
        -s compiler.version=20 \
        -s compiler.libcxx=libc++ \
        -o use_mold=True \
        -o enable_lcov=True \
        --build=missing \
    && rm -r ../light/
