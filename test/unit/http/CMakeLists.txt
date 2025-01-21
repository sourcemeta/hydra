noa_googletest(NAMESPACE sourcemeta PROJECT hydra NAME http
  FOLDER "Hydra/HTTP"
  SOURCES time_test.cc status_test.cc method_test.cc
  header_test.cc mime_test.cc)

target_link_libraries(sourcemeta_hydra_http_unit
  PRIVATE sourcemeta::hydra::http)
