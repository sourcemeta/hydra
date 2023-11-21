if(DEFINED ENV{VCPKG_ROOT})
  set(VCPKG_CMAKE_TOOLCHAIN $ENV{VCPKG_ROOT})
  cmake_path(APPEND VCPKG_CMAKE_TOOLCHAIN scripts buildsystems vcpkg.cmake)
else()
  # Attempt to find vcpkg from standard locations
  # Useful for GitHub Actions, which does not set VCPKG_ROOT
  find_file(VCPKG_CMAKE_TOOLCHAIN
    NAMES scripts/buildsystems/vcpkg.cmake
    PATHS C:/src/vcpkg C:/dev/vcpkg C:/vcpkg
    NO_DEFAULT_PATH)
endif()
if(EXISTS "${VCPKG_CMAKE_TOOLCHAIN}")
  message(STATUS "Using VCPKG toolchain: ${VCPKG_CMAKE_TOOLCHAIN}")
  set(CMAKE_TOOLCHAIN_FILE "${VCPKG_CMAKE_TOOLCHAIN}" CACHE STRING "VCPKG toolchain file")
else()
  message(FATAL_ERROR "Could NOT find VCPKG")
endif()
