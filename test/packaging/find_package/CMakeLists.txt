cmake_minimum_required(VERSION 3.18)
project(core_hello VERSION 0.0.1 LANGUAGES CXX)
find_package(Hydra REQUIRED)
add_executable(hello hello.cc)
set_target_properties(hello PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF)

target_link_libraries(hello PRIVATE ZLIB::ZLIB)
if(SOURCEMETA_HYDRA_USE_SYSTEM_OPENSSL)
  target_compile_definitions(hello PRIVATE SOURCEMETA_HYDRA_USE_SYSTEM_OPENSSL)
  target_link_libraries(hello PRIVATE OpenSSL::SSL OpenSSL::Crypto)
elseif(NOT WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "MSYS")
  target_link_libraries(hello PRIVATE MbedTLS::mbedtls)
endif()
target_link_libraries(hello PRIVATE Nghttp2::nghttp2)
if(NOT WIN32 AND NOT CMAKE_SYSTEM_NAME STREQUAL "MSYS")
  target_link_libraries(hello PRIVATE c-ares::cares)
endif()
target_link_libraries(hello PRIVATE PSL::psl)
target_link_libraries(hello PRIVATE CURL::libcurl)
target_link_libraries(hello PRIVATE CPR::cpr)
