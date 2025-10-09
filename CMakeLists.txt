cmake_minimum_required(VERSION 3.16)
# We use live-at-head instead of versioning
project(hydra VERSION 0.0.0 LANGUAGES C CXX)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

option(SOURCEMETA_HYDRA_INSTALL "Install the Sourcemeta Hydra library" ON)
option(SOURCEMETA_HYDRA_TESTS "Build the Sourcemeta Hydra tests" OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  set(HYDRA_COMPILER_LLVM ON)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(HYDRA_COMPILER_GCC ON)
elseif(MSVC)
  set(HYDRA_COMPILER_MSVC ON)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if(WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "MSYS")
  add_compile_definitions(_POSIX_C_SOURCE=200809L)
endif()

find_package(ZLIB REQUIRED)

if(NOT WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "MSYS")
  find_package(MbedTLS REQUIRED)
endif()

find_package(Nghttp2 REQUIRED)

if(NOT WIN32 AND NOT CMAKE_SYSTEM_NAME STREQUAL "MSYS")
  find_package(CAres REQUIRED)
endif()

find_package(PSL REQUIRED)
find_package(CURL REQUIRED)
find_package(CPR REQUIRED)

if(SOURCEMETA_HYDRA_INSTALL)
  include(GNUInstallDirs)
  include(CMakePackageConfigHelpers)
  configure_package_config_file(
    config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    COMPATIBILITY SameMajorVersion)
  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
    COMPONENT sourcemeta_${PROJECT_NAME}_dev)
endif()

if(SOURCEMETA_HYDRA_TESTS)
  enable_testing()
  add_subdirectory(test/e2e)
  if(PROJECT_IS_TOP_LEVEL)
    add_subdirectory(test/packaging)
  endif()
endif()
