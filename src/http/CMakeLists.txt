set(HYDRA_PUBLIC_HEADERS include/sourcemeta/hydra/http.h)
set(HYDRA_PRIVATE_HEADERS
  include/sourcemeta/hydra/http_method.h
  include/sourcemeta/hydra/http_status.h
  include/sourcemeta/hydra/http_error.h
  include/sourcemeta/hydra/http_stream.h
  include/sourcemeta/hydra/http_request.h
  include/sourcemeta/hydra/http_response.h
  "${CMAKE_CURRENT_BINARY_DIR}/http_export.h")

add_library(sourcemeta_hydra_http
  ${HYDRA_PUBLIC_HEADERS} ${HYDRA_PRIVATE_HEADERS}
  status.cc stream_curl.cc request.cc response.cc)
sourcemeta_hydra_add_compile_options(sourcemeta_hydra_http)
add_library(sourcemeta::hydra::http
  ALIAS sourcemeta_hydra_http)
target_include_directories(sourcemeta_hydra_http
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
set_target_properties(sourcemeta_hydra_http PROPERTIES
  OUTPUT_NAME sourcemeta_hydra_http
  PUBLIC_HEADER "${HYDRA_PUBLIC_HEADERS}"
  PRIVATE_HEADER "${HYDRA_PRIVATE_HEADERS}"
  EXPORT_NAME hydra::http
  FOLDER "Hydra/HTTP")

target_link_libraries(sourcemeta_hydra_http PRIVATE CURL::libcurl)

include(GenerateExportHeader)
generate_export_header(sourcemeta_hydra_http
  EXPORT_FILE_NAME http_export.h)
set_target_properties(sourcemeta_hydra_http PROPERTIES
  SOVERSION "${PROJECT_VERSION_MAJOR}"
  VERSION "${PROJECT_VERSION}")

# To find the generated files
target_include_directories(sourcemeta_hydra_http
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")

# Installation
include(GNUInstallDirs)
install(TARGETS sourcemeta_hydra_http
  EXPORT sourcemeta_hydra_http
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sourcemeta/hydra"
    COMPONENT sourcemeta_hydra_dev
  PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sourcemeta/hydra"
    COMPONENT sourcemeta_hydra_dev
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    COMPONENT sourcemeta_hydra
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    COMPONENT sourcemeta_hydra
    NAMELINK_COMPONENT sourcemeta_hydra_dev
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    COMPONENT sourcemeta_hydra_dev)
install(EXPORT sourcemeta_hydra_http
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
  NAMESPACE sourcemeta::
  COMPONENT sourcemeta_hydra_dev)
