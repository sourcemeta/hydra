FROM debian:bookworm

RUN apt-get --yes update && apt-get install --yes --no-install-recommends \
  build-essential clang ca-certificates cmake \
  && apt-get clean && rm -rf /var/lib/apt/lists/*

COPY cmake /source/cmake
COPY vendor /source/vendor
COPY CMakeLists.txt /source/CMakeLists.txt
COPY DEPENDENCIES /source/DEPENDENCIES
COPY test /source/test
COPY config.cmake.in /source/config.cmake.in
COPY Makefile /source/Makefile

ARG SOURCEMETA_HYDRA_CC=gcc
ARG SOURCEMETA_HYDRA_CXX=g++
ARG SOURCEMETA_HYDRA_SHARED=OFF

RUN make -C /source CC=${SOURCEMETA_HYDRA_CC} CXX=${SOURCEMETA_HYDRA_CXX} SHARED=${SOURCEMETA_HYDRA_SHARED}
