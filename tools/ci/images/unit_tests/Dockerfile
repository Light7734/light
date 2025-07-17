FROM alpine:latest

RUN apk add --no-cache \
    bash \
    clang \
    llvm \
    cmake \
    git \
    make \
    g++ \
    python3 \
    py3-pip \
    mesa-dev \
    mesa-gl \
    pkgconf \
    ninja-build \
    mold


RUN pip install --no-cache-dir --break-system-packages conan gitpython \
    && conan profile detect

RUN clang --version  \
    && conan --version \
    && pip --version \
    && cmake --version \
    && g++ --version \
    && clang --version \
    && ninja --version \
    && mold --version

RUN git clone 'https://git.light7734.com/light7734/light.git' --recursive \
    && cd light \
    && conan install . \
        -s build_type=Debug \
        -c tools.system.package_manager:mode=install \
        --build=missing \
    && conan install . \
        -s build_type=Release \
        -c tools.system.package_manager:mode=install \
        --build=missing
