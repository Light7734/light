FROM archlinux:latest

## Configurations ##
RUN \
mkdir /msan \
&& echo 'src:*' > /msan/ignorelist_all_sources \
&& sed -i 's/^#ParallelDownloads = .*/ParallelDownloads = 8/' /etc/pacman.conf \
&& echo 'NoExtract = usr/share/{man,doc,info}/*' >> /etc/pacman.conf

## Packages ##
RUN \
pacman -Syyu --noconfirm --needed --disable-download-timeout \
    afl++ \
    afl-utils \
    base-devel \
    bash \
    cbindgen \
    clang \
    cmake \
    curl \
    debuginfod \
    directx-headers \
    elfutils \
    expat \
    gcc \
    gcc-libs \
    gdb \
    git \
    glibc \
    glm \
    glslang \
    libc++ \
    libclc \
    libdrm \
    libelf \
    libglvnd \
    libinput \
    libpciaccess \
    libpng \
    libunwind \
    libva \
    libx11 \
    libxcb \
    libxdamage \
    libxext \
    libxfixes \
    libxi \
    libxinerama \
    libxml2 \
    libxpresent \
    libxrandr \
    libxshmfence \
    libxxf86vm \
    lm_sensors \
    llvm \
    lz4 \
    meson \
    mold \
    ninja \
    python \
    python-distlib \
    python-distutils-extra \
    python-jsonschema \
    python-mako \
    python-packaging \
    python-ply \
    python-pyaml \
    qt5-base \
    qt6-base \
    rust \
    rust-bindgen \
    spirv-llvm-translator \
    spirv-tools \
    systemd-libs \
    valgrind \
    vulkan-headers \
    vulkan-icd-loader \
    vulkan-tools \
    vulkan-validation-layers \
    wayland \
    wayland-protocols \
    wget \
    xcb-proto \
    xcb-util \
    xcb-util-cursor \
    xcb-util-keysyms \
    xcb-util-wm \
    xorg-server-xvfb \
    xorg-util-macros \
    xorgproto \
    xtrans \
    zlib \
    zstd \
&& pacman -Scc --noconfirm

## Libc++ ##
RUN \
git clone \
    --branch llvmorg-20.1.8 \
    --depth=1 \
    https://github.com/llvm/llvm-project.git

RUN git clone \
    --branch='25.2'\
    --depth=1 \
    https://gitlab.freedesktop.org/mesa/mesa.git

RUN wget https://x.org/releases/individual/lib/libxcb-1.17.0.tar.xz
RUN wget https://x.org/releases/individual/lib/libX11-1.8.12.tar.xz
RUN wget 'https://sdk.lunarg.com/sdk/download/1.4.328.1/linux/vulkansdk-linux-x86_64-1.4.328.1.tar.xz'

RUN cd llvm-project/ \
\
&& cmake \
    -S ./runtimes \
    -B ./build-lsan \
    -G Ninja \
    -D CMAKE_LINKER_TYPE="MOLD" \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_INSTALL_PREFIX=/libcxx_lsan \
    -D CMAKE_C_COMPILER=$(which clang) \
    -D CMAKE_CXX_COMPILER=$(which clang++) \
    -D LLVM_ENABLE_PROJECTS="clang;compiler-rt" \
    -D LLVM_ENABLE_RUNTIMES="libcxx;libcxxabi" \
    -D LLVM_TARGETS_TO_BUILD="X86;SPIRV" \
    -D LLVM_ENABLE_PIC=ON \
    -D LIBCXX_INSTALL_MODULES=ON \
    -D LIBCXXABI_USE_LLVM_UNWINDER=OFF \
    -D LLVM_USE_SANITIZER=Leaks \
    -D LLVM_USE_LINKER="MOLD" \
&& cd ./build-lsan/ && ninja cxx cxxabi && ninja install-cxx install-cxxabi && cd ../ \
\
&& cmake \
    -S ./runtimes \
    -B ./build-msan \
    -G Ninja \
    -D CMAKE_LINKER_TYPE="MOLD" \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_INSTALL_PREFIX=/libcxx_msan \
    -D CMAKE_C_COMPILER=$(which clang) \
    -D CMAKE_CXX_COMPILER=$(which clang++) \
    -D LLVM_ENABLE_PROJECTS="clang;compiler-rt" \
    -D LLVM_ENABLE_RUNTIMES="libcxx;libcxxabi" \
    -D LLVM_TARGETS_TO_BUILD="X86;SPIRV" \
    -D LLVM_ENABLE_PIC=ON \
    -D LIBCXX_INSTALL_MODULES=ON \
    -D LIBCXXABI_USE_LLVM_UNWINDER=OFF \
    -D LLVM_USE_SANITIZER=MemoryWithOrigins \
    -D LLVM_USE_LINKER="MOLD" \
&& cd ./build-msan/ && ninja cxx cxxabi && ninja install-cxx install-cxxabi && cd ../

RUN cd llvm-project/


## libxcb ##
RUN \
tar xf libxcb-1.17.0.tar.xz  \
&& cd libxcb-1.17.0  \
&& export CC=clang \
&& export CFLAGS=" \
    -fsanitize=memory \
    -fsanitize-memory-track-origins \
    -fsanitize-ignorelist=/msan/ignorelist_all_sources \
    -fno-omit-frame-pointer \
    -g \
    -fPIC" \
&& export LDFLAGS=" \
    -fsanitize=memory \
    -fsanitize-memory-track-origins \
    -fsanitize-ignorelist=/msan/ignorelist_all_sources \
    -fno-omit-frame-pointer \
    -g \
    -fPIC" \
&& ./configure \
    --prefix=/msan \
    --disable-static \
    --without-doxygen \
&& make && make install \
&& cd .. && rm -rf libxcb-1.17.0 libxcb-1.17.0.tar.xz

## libx11 ##
RUN \
tar xf libX11-1.8.12.tar.xz  \
&& cd libX11-1.8.12  \
&& export CC=clang \
&& export CFLAGS=" \
-fsanitize=memory \
-fsanitize-memory-track-origins \
-fsanitize-ignorelist=/msan/ignorelist_all_sources \
-fno-omit-frame-pointer \
-g \
-fPIC" \
&& export LDFLAGS=" \
-fsanitize=memory \
-fsanitize-memory-track-origins \
-fsanitize-ignorelist=/msan/ignorelist_all_sources \
-fno-omit-frame-pointer \
-g \
-fPIC" \
&& export PKG_CONFIG_PATH=/msan/lib/pkgconfig:$PKG_CONFIG_PATH \
&& ./configure \
    --prefix=/msan \
    --disable-static \
&& make && make install \
&& cd .. && rm -rf libX11-1.8.12 libX11-1.8.12.tar.xz



## Vulkan SDK ##
RUN \
tar xf 'vulkansdk-linux-x86_64-1.4.328.1.tar.xz' \
&& cd /1.4.328.1 \
&& chmod +x ./vulkansdk \
&& chmod +x ./setup-env.sh \
&& export CC="$(which clang)" \
&& export CXX="$(which clang++)" \
&& export CXXFLAGS="\
        -fsanitize=memory \
        -fsanitize-memory-track-origins \
        -fsanitize-ignorelist=/msan/ignorelist_all_sources \
        -fno-omit-frame-pointer \
        -g \
        -std=c++23 \
        -nostdinc++ \
        -isystem /libcxx_msan/include/c++/v1/"\
&& export CFLAGS="\
        -fsanitize=memory \
        -fsanitize-memory-track-origins \
        -fno-omit-frame-pointer \
        -g" \
&& export LDFLAGS="\
    -fsanitize=memory \
    -fsanitize-memory-track-origins \
    -fsanitize-ignorelist=/msan/ignorelist_all_sources \
    -g \
    -std=c++23 \
    -L/msan/lib -Wl,-rpath,/msan/lib \
    -L/libcxx_msan/lib -Wl,-rpath,/libcxx_msan/lib \
    -lc++ \
    -lc++abi" \
&& ./vulkansdk \
    --debug \
    --skip-installing-deps \
    --numjobs `nproc` \
    vulkan-loader \
    spirv-tools

## Mesa ##



RUN \
export build_llvm=/build-llvm \
&& export build_path=/b_llvm_normal \
&& export repo=/llvm-project \
\
&& cmake \
    -S $repo/llvm \
    -G Ninja \
    -B $build_path \
    -D CMAKE_BUILD_TYPE=Release \
    -D LLVM_ENABLE_PROJECTS="clang;lld;compiler-rt" \
    -D CMAKE_C_COMPILER=$(which clang) \
    -D CMAKE_CXX_COMPILER=$(which clang++) \
    -D CMAKE_INSTALL_PREFIX=/opt/llvm-normal \
&& ninja -C $build_path install

RUN \
export CXXFLAGS="\
        -fsanitize=memory \
        -fsanitize-memory-track-origins \
        -fsanitize-ignorelist=/msan/ignorelist_all_sources \
        -fno-omit-frame-pointer \
        -g \
        -std=c++23 \
        -nostdinc++ \
        -isystem /libcxx_msan/include/c++/v1/"\
&& export CFLAGS="\
        -fsanitize=memory \
        -fsanitize-memory-track-origins \
        -fno-omit-frame-pointer \
        -g" \
&& export LDFLAGS="\
    -fsanitize=memory \
    -fsanitize-memory-track-origins \
    -fsanitize-ignorelist=/msan/ignorelist_all_sources \
    -g \
    -std=c++23 \
    -L/msan/lib -Wl,-rpath,/msan/lib \
    -L/libcxx_msan/lib -Wl,-rpath,/libcxx_msan/lib \
    -lc++ \
    -lc++abi" \
&& export build_path=/b_llvm_msan \
&& export repo=/llvm-project \
\
&& cmake \
    -S $repo/llvm \
    -G Ninja \
    -B $build_path \
    -D CMAKE_BUILD_TYPE=Release \
    -D LLVM_ENABLE_PROJECTS="clang;lld" \
    -D LLVM_TARGETS_TO_BUILD="X86;SPIRV" \
    -D LLVM_ENABLE_PIC=ON \
    -D LLVM_NATIVE_TOOL_DIR=/opt/llvm-normal/bin/ \
    -D LLVM_USE_SANITIZER=MemoryWithOrigins \
    -D LLVM_TABLEGEN=/opt/llvm-normal/bin/llvm-tblgen \
    -D LLVM_CONFIG_PATH=/opt/llvm-normal/bin/llvm-config \
    -D CMAKE_C_COMPILER=/opt/llvm-normal/bin/clang \
    -D CMAKE_CXX_COMPILER=/opt/llvm-normal/bin/clang++ \
    -D CMAKE_INSTALL_PREFIX=/opt/llvm-msan \
&& ninja -C $build_path install

# && cmake \
#     -G Ninja \
#     -S $llvm/llvm \
#     -B $build_llvm \
#     -D LLVM_INSTALL_UTILS=ON \
#     -D CMAKE_INSTALL_PREFIX=$installprefix \
#     -D CMAKE_BUILD_TYPE=Release \
#     -D LLVM_TARGETS_TO_BUILD="X86;SPIRV" \
#     -D CMAKE_C_COMPILER=$(which clang) \
#     -D CMAKE_CXX_COMPILER=$(which clang++) \
# \
#     -D LLVM_USE_SANITIZER=MemoryWithOrigins \
#     -D LIBCXXABI_USE_LLVM_UNWINDER=OFF \
# \
# && ninja -C $build_llvm install
#
# && cmake  \
#     -G Ninja  \
#     -S $llvm/clang  \
#     -B $build_clang \
#     -D LLVM_EXTERNAL_LIT=$build_llvm/utils/lit \
#     -D LLVM_ROOT=$installprefix \
# \
# && ninja -C $build_clang

RUN \
cd /mesa \
&& export CXX='clang++' \
&& export CC='clang' \
&& export CFLAGS="-fsanitize=memory  -fsanitize-memory-track-origins  -fno-omit-frame-pointer  -g" \
&& export CXXFLAGS="-fsanitize=memory -fsanitize-memory-track-origins -fno-omit-frame-pointer -g -nostdinc++ -isystem /libcxx_msan/include/c++/v1/" \
&& export LDFLAGS="-fsanitize=memory -fsanitize-memory-track-origins -g -L/libcxx_msan/lib -Wl,-rpath,/libcxx_msan/lib -L/msan/lib -Wl,-rpath,/msan/lib -lc++ -lc++abi"  \
&& export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:$PATH" \
&& meson setup ./ _build \
    -D build-tests=false  \
    -D enable-glcpp-tests=false  \
    -D build-radv-tests=false  \
    -D build-aco-tests=false  \
    -D install-intel-gpu-tests=false  \
    -D gallium-mediafoundation-test=false  \
    -D android-libbacktrace=disabled  \
    -D split-debug=disabled  \
    -D b_ndebug=true  \
    -D b_lto=false  \
    -D egl=enabled  \
    -D gallium-drivers=r300,r600,radeonsi,nouveau,virgl,svga,softpipe,llvmpipe,i915,iris,crocus,zink  \
    -D gallium-extra-hud=true  \
    -D gallium-rusticl=true  \
    -D gallium-va=enabled  \
    -D gbm=enabled  \
    -D gles1=disabled  \
    -D gles2=enabled  \
    -D glvnd=enabled  \
    -D glx=dri  \
    -D libunwind=enabled  \
    -D llvm=enabled  \
    -D lmsensors=disabled  \
    -D microsoft-clc=disabled  \
    -D platforms=x11,wayland  \
    -D valgrind=disabled  \
    -D video-codecs=all  \
    -D vulkan-drivers=amd,intel,intel_hasvk,swrast,virtio,nouveau  \
    -D vulkan-layers=device-select,intel-nullhw,overlay  \
    -D tools=''  \
    -D zstd=enabled  \
    -D buildtype=plain  \
    -D prefix=/usr  \
    -D sysconfdir=/etc  \
    --wrap-mode=nofallback  \
    --force-fallback-for=syn,paste,rustc-hash  \
&& ninja -C _build

# RUN cd mesa/ \
# && source '/1.4.328.1/setup-env.sh' \
# && export CXX='clang++' \
# && export CC='clang' \
# && export CFLAGS="\
#         -fsanitize=memory \
#         -fsanitize-memory-track-origins \
#         -fno-omit-frame-pointer \
#         -g" \
# && export CXXFLAGS="\
#         -fsanitize=memory \
#         -fsanitize-memory-track-origins \
#         -fno-omit-frame-pointer \
#         -g \
#         -nostdinc++ \
#         -isystem /libcxx_msan/include/c++/v1/"\
# && export LDFLAGS="\
#     -fsanitize=memory \
#     -fsanitize-memory-track-origins \
#     -g \
#     -L/libcxx_msan/lib -Wl,-rpath,/libcxx_msan/lib \
#     -L/msan/lib -Wl,-rpath,/msan/lib \
#     -lc++ \
#     -lc++abi" \
# && meson setup ./ _build  \
#     -D build-tests=false \
#     -D enable-glcpp-tests=false \
#     -D build-radv-tests=false \
#     -D build-aco-tests=false \
#     -D install-intel-gpu-tests=false \
#     -D gallium-mediafoundation-test=false \
#     -D android-libbacktrace=disabled \
#     -D split-debug=disabled \
#     -D b_ndebug=true \
#     -D b_lto=false \
#     -D egl=enabled \
#     -D gallium-drivers=r300,r600,radeonsi,nouveau,virgl,svga,softpipe,llvmpipe,i915,iris,crocus,zink \
#     -D gallium-extra-hud=true \
#     -D gallium-rusticl=true \
#     -D gallium-va=enabled \
#     -D gbm=enabled \
#     -D gles1=disabled \
#     -D gles2=enabled \
#     -D glvnd=enabled \
#     -D glx=dri \
#     -D libunwind=enabled \
#     -D llvm=enabled \
#     -D lmsensors=disabled \
#     -D microsoft-clc=disabled \
#     -D platforms=x11,wayland \
#     -D valgrind=disabled \
#     -D video-codecs=all \
#     -D vulkan-drivers=amd,intel,intel_hasvk,swrast,virtio,nouveau \
#     -D vulkan-layers=device-select,intel-nullhw,overlay \
#     -D tools='' \
#     -D zstd=enabled \
#     -D buildtype=plain \
#     -D prefix=/usr \
#     -D sysconfdir=/etc \
#     --wrap-mode=nofallback \
#     --force-fallback-for=syn,paste,rustc-hash \
# && ninja -C _build
#
