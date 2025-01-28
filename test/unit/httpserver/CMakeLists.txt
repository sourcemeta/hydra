sourcemeta_googletest(NAMESPACE sourcemeta PROJECT hydra NAME httpserver
  FOLDER "Hydra/HTTP Server"
  SOURCES logger_test.cc)

target_link_libraries(sourcemeta_hydra_httpserver_unit
  PRIVATE sourcemeta::hydra::httpserver)
