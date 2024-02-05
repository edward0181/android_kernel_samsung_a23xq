#!/bin/bash

#make clean && make mrproper
#export ARCH=arm64
mkdir out

#BUILD_CROSS_COMPILE=$(pwd)/toolchain/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-
#KERNEL_LLVM_BIN=$(pwd)/toolchain/llvm-arm-toolchain-ship/10.0/bin/clang
#CLANG_TRIPLE=aarch64-linux-gnu-
#KERNEL_MAKE_ENV="DTC_EXT=$(pwd)/tools/dtc CONFIG_BUILD_ARM64_DT_OVERLAY=y"

#make -j64 -C $(pwd) O=$(pwd)/out $KERNEL_MAKE_ENV ARCH=arm64 CROSS_COMPILE=$BUILD_CROSS_COMPILE REAL_CC=$KERNEL_LLVM_BIN CLANG_TRIPLE=$CLANG_TRIPLE CONFIG_SECTION_MISMATCH_WARN_ONLY=y vendor/a23xq_eur_open_defconfig
#make -j64 -C $(pwd) O=$(pwd)/out $KERNEL_MAKE_ENV ARCH=arm64 CROSS_COMPILE=$BUILD_CROSS_COMPILE REAL_CC=$KERNEL_LLVM_BIN CLANG_TRIPLE=$CLANG_TRIPLE CONFIG_SECTION_MISMATCH_WARN_ONLY=y
 
#cp out/arch/arm64/boot/Image $(pwd)/arch/arm64/boot/Image


export ARCH=arm64
#export LLVM=1
export CLANG_PREBUILT_BIN=$(pwd)/toolchain/clang-proton/bin
export PATH=$PATH:$CLANG_PREBUILT_BIN
BUILD_CROSS_COMPILE=$(pwd)/toolchain/clang-proton/bin/aarch64-linux-gnu-
KERNEL_LLVM_BIN=$(pwd)/toolchain/clang-proton/bin/clang
CLANG_TRIPLE=aarch64-linux-gnu-
KERNEL_MAKE_ENV="CONFIG_BUILD_ARM64_DT_OVERLAY=y"

#mkdir out
make -j7 -C $(pwd) O=$(pwd)/out $KERNEL_MAKE_ENV ARCH=arm64 CROSS_COMPILE=$BUILD_CROSS_COMPILE CC=$KERNEL_LLVM_BIN CLANG_TRIPLE=$CLANG_TRIPLE CONFIG_SECTION_MISMATCH_WARN_ONLY=y vendor/temp_defconfig
#make -j7 -C $(pwd) O=$(pwd)/out $KERNEL_MAKE_ENV ARCH=arm64 CROSS_COMPILE=$BUILD_CROSS_COMPILE CC=$KERNEL_LLVM_BIN CLANG_TRIPLE=$CLANG_TRIPLE CONFIG_SECTION_MISMATCH_WARN_ONLY=y menuconfig
make -j7 -C $(pwd) O=$(pwd)/out $KERNEL_MAKE_ENV ARCH=arm64 CROSS_COMPILE=$BUILD_CROSS_COMPILE CC=$KERNEL_LLVM_BIN CLANG_TRIPLE=$CLANG_TRIPLE CONFIG_SECTION_MISMATCH_WARN_ONLY=y
make -j7 -C $(pwd) O=$(pwd)/out $KERNEL_MAKE_ENV ARCH=arm64 CROSS_COMPILE=$BUILD_CROSS_COMPILE CC=$KERNEL_LLVM_BIN CLANG_TRIPLE=$CLANG_TRIPLE CONFIG_SECTION_MISMATCH_WARN_ONLY=y modules_install INSTALL_MOD_STRIP=1 INSTALL_MOD_PATH=kernel_modules
make -j7 -C $(pwd) O=$(pwd)/out $KERNEL_MAKE_ENV ARCH=arm64 CROSS_COMPILE=$BUILD_CROSS_COMPILE CC=$KERNEL_LLVM_BIN CLANG_TRIPLE=$CLANG_TRIPLE CONFIG_SECTION_MISMATCH_WARN_ONLY=y modules_prepare

#make -j7 -C $(pwd) O=$(pwd)/out CONFIG_BUILD_ARM64_DT_OVERLAY=y ARCH=arm64 CROSS_COMPILE=/workspaces/aarch64-linux-android-4.9/bin/aarch64-linux-android- REAL_CC=/workspaces/clang/bin/clang CLANG_TRIPLE=aarch64-linux-gnu- CONFIG_SECTION_MISMATCH_WARN_ONLY=y modules_prepare

cp out/arch/arm64/boot/Image $(pwd)/arch/arm64/boot/Image