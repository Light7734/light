FROM archlinux:base-devel

RUN pacman -Syu --noconfirm --disable-download-timeout \
    && pacman -S --noconfirm --needed --disable-download-timeout reflector \
    && reflector --verbose --latest 10 --protocol https --sort rate --save /etc/pacman.d/mirrorlist \
    && sed -i 's/^#ParallelDownloads = .*/ParallelDownloads = 9/' /etc/pacman.conf

RUN pacman -S --noconfirm --needed --disable-download-timeout \
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
    ninja \
    mold \
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
    libxi \
    xcb-util-cursor

RUN pip install --no-cache-dir --break-system-packages \
    conan \
    gitpython \
    && conan profile detect

RUN clang --version  \
    && conan --version \
    && pip --version \
    && cmake --version \
    && g++ --version \
    && clang --version \
    && ninja --version \
    && mold --version

# We `build` instead of `install` to make sure the project can be built with the current image state.
RUN git clone 'https://git.light7734.com/light7734/light.git' --depth=1 \
    && cd light \
    && conan build . \
    -c tools.system.package_manager:mode=install \
    -c tools.cmake.cmaketoolchain:generator=Ninja \
    -c tools.build:compiler_executables='{"c": "gcc", "cpp": "g++"}' \
    -s build_type=Release \
    -s compiler=gcc \
    -s compiler.version=15 \
    -s compiler.libcxx=libstdc++ \
    -o enable_unit_tests=True \
    -o enable_fuzz_tests=False \
    -o enable_llvm_coverage=False \
    -o enable_static_analysis=False \
    -o use_mold=True \
    -o export_compile_commands=False \
    --build=missing \
    && rm -rf ../light
