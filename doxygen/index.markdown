Getting Started
===============

@tableofcontents

Hydra is a convenience networking library for modern C++. It targets C++20 and
supports the Clang, GCC, and MSVC compilers on macOS, GNU/Linux, and Windows.

Installation
------------

### As a git submodule

```sh
# Add the project as a submodule, in this case to deps/hydra
$ git submodule add https://github.com/sourcemeta/hydra.git deps/hydra

# Add the project as a CMake subdirectory
add_subdirectory("${PROJECT_SOURCE_DIR}/deps/hydra")

# Link your targets accordingly
target_link_libraries(my_executable_or_library PUBLIC sourcemeta::hydra::http)
```

### Using FetchContent

```cmake
cmake_minimum_required(VERSION 3.14)
project(my_project)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  hydra
  URL https://github.com/sourcemeta/hydra/archive/<commit-sha>.zip
  DOWNLOAD_EXTRACT_TIMESTAMP NO)
FetchContent_MakeAvailable(hydra)

add_executable(my_example ...)
target_link_libraries(my_example PUBLIC sourcemeta::hydra::http)
```

### Using find_package

Assuming you have installed Hydra in a place where CMake can find the
package config file:

```sh
find_package(Hydra REQUIRED)

# This package also supports component-based inclusion
find_package(Hydra REQUIRED COMPONENTS http)

# Link your targets accordingly
target_link_libraries(my_executable_or_library PUBLIC sourcemeta::hydra::http)
```

CMake
-----

### Options

| Option                      | Type    | Default | Description                             |
|-----------------------------|---------|---------|-----------------------------------------|
| `HYDRA_HTTP`                | Boolean | `ON`    | Build the Hydra HTTP client library     |
| `HYDRA_TESTS`               | Boolean | `OFF`   | Build the Hydra tests                   |
| `HYDRA_DOCS`                | Boolean | `OFF`   | Build the Hydra docs                    |
| `HYDRA_INSTALL`             | Boolean | `ON`    | Install the Hydra library               |
| `HYDRA_ADDRESS_SANITIZER`   | Boolean | `OFF`   | Enable the address sanitizer            |
| `HYDRA_UNDEFINED_SANITIZER` | Boolean | `OFF`   | Enable the undefined behavior sanitizer |

### Components

If you install Hydra from source, keep in mind that the project is split
into a set of CMake components:

| Component                        | Description                                    |
|----------------------------------|------------------------------------------------|
| `sourcemeta_hydra`         | The core Hydra libraries                |
| `sourcemeta_hydra_dev`     | The Hydra headers and development files |

Contributing
------------

Hydra makes use of the [CMake](https://cmake.org) build system. You can
configure, build and test the project as follows:

```sh
cmake -S . -B ./build \
  -DCMAKE_BUILD_TYPE:STRING=<Debug|Release> \
  -DCMAKE_COMPILE_WARNING_AS_ERROR:BOOL=ON \
  -DHYDRA_DOCS:BOOL=ON \
  -DHYDRA_TESTS:BOOL=ON
# Format the code
cmake --build ./build --config <Debug|Release> --target clang_format
# Build the project
cmake --build ./build --config <Debug|Release>
# Run the test suite. For information on running the e2e test suite,
# refer to the GitHub Actions CI configuration.
ctest --test-dir ./build --build-config <Debug|Release> --output-on-failure --progress --exclude-regex e2e
```

Or simply run:

```sh
# On UNIX-based systems
make
# On Windows
nmake
```
