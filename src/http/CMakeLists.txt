noa_library(NAMESPACE sourcemeta PROJECT hydra NAME http
  FOLDER "Hydra/HTTP"
  PRIVATE_HEADERS method.h status.h error.h stream.h request.h response.h time.h
  SOURCES method.cc status.cc stream_curl.cc request.cc response.cc time.cc)

if(HYDRA_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT hydra NAME http)
endif()

target_link_libraries(sourcemeta_hydra_http PRIVATE CURL::libcurl)
sourcemeta_hydra_add_compile_options(sourcemeta_hydra_http)
