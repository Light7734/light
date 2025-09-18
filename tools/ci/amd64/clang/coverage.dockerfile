FROM archlinux:latest

RUN pacman -Syu --noconfirm --disable-download-timeout \
    && pacman -S  --noconfirm --disable-download-timeout reflector \
    && reflector --verbose --latest 10 --protocol https --sort rate --save /etc/pacman.d/mirrorlist \
    && sed -i 's/^#ParallelDownloads = .*/ParallelDownloads = 8/' /etc/pacman.conf \

RUN pacman -S --noconfirm --disable-download-timeout \
    bash \
    base-devel \
    git \
    cmake \
    python \
    python-pip \
    clang \
    gcc \
    llvm \
    mesa \
    mold \
    ninja \
    curl \
    wget \
    zlib \
    libc++ \
    libinput \
    xorg-server-xvfb \
    libx11 \
    libxrandr \
    libxinerama \
    libxcursor \
    libxi

RUN pip install --no-cache-dir --break-system-packages conan gitpython \
    && conan profile detect

RUN pip --version \
    && conan --version \
    && cmake --version \
    && g++ --version \
    && clang --version \
    && ninja --version \
    && mold --version \
    && llvm-profdata --version \
    && llvm-cov --version

RUN git clone 'https://git.light7734.com/light7734/light.git' \
    && cd light \
    && conan build . \
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
