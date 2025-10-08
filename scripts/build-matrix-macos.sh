#!/bin/sh

set -o errexit
set -o nounset

echo "==========================================="
echo "MACOS: LLVM (static)"
echo "==========================================="

make clean
make CC=clang CXX=clang++ SHARED=OFF

echo "==========================================="
echo "MACOS: LLVM (shared)"
echo "==========================================="

make clean
make CC=clang CXX=clang++ SHARED=ON

echo "==========================================="
echo "MACOS: GCC (static)"
echo "==========================================="

make clean
make CC=gcc-15 CXX=g++-15 SHARED=OFF

echo "==========================================="
echo "MACOS: GCC (shared)"
echo "==========================================="

make clean
make CC=gcc-15 CXX=g++-15 SHARED=ON

echo "==========================================="
echo "LINUX: GCC (static)"
echo "==========================================="

docker build . --progress plain \
  --build-arg SOURCEMETA_HYDRA_CC=gcc \
  --build-arg SOURCEMETA_HYDRA_CXX=g++ \
  --build-arg SOURCEMETA_HYDRA_SHARED=OFF

echo "==========================================="
echo "LINUX: GCC (shared)"
echo "==========================================="

docker build . --progress plain \
  --build-arg SOURCEMETA_HYDRA_CC=gcc \
  --build-arg SOURCEMETA_HYDRA_CXX=g++ \
  --build-arg SOURCEMETA_HYDRA_SHARED=ON

echo "==========================================="
echo "LINUX: LLVM (static)"
echo "==========================================="

docker build . --progress plain \
  --build-arg SOURCEMETA_HYDRA_CC=clang \
  --build-arg SOURCEMETA_HYDRA_CXX=clang++ \
  --build-arg SOURCEMETA_HYDRA_SHARED=OFF

echo "==========================================="
echo "LINUX: LLVM (shared)"
echo "==========================================="

docker build . --progress plain \
  --build-arg SOURCEMETA_HYDRA_CC=clang \
  --build-arg SOURCEMETA_HYDRA_CXX=clang++ \
  --build-arg SOURCEMETA_HYDRA_SHARED=ON
