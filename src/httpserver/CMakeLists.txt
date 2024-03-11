noa_library(NAMESPACE sourcemeta PROJECT hydra NAME httpserver
  FOLDER "Hydra/HTTP Server"
  PRIVATE_HEADERS uuid.h
  SOURCES uuid.cc)

if(HYDRA_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT hydra NAME httpserver)
endif()

target_link_libraries(sourcemeta_hydra_httpserver PUBLIC sourcemeta::hydra::http)
sourcemeta_hydra_add_compile_options(sourcemeta_hydra_httpserver)
