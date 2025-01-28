add_executable(sourcemeta_hydra_httpserver_e2e_stub stub.cc)
target_link_libraries(sourcemeta_hydra_httpserver_e2e_stub PRIVATE
  sourcemeta::hydra::httpserver)
target_link_libraries(sourcemeta_hydra_httpserver_e2e_stub PRIVATE
  sourcemeta::core::json)
target_link_libraries(sourcemeta_hydra_httpserver_e2e_stub PRIVATE
  sourcemeta::core::jsonschema)
target_compile_definitions(sourcemeta_hydra_httpserver_e2e_stub PRIVATE
  STATIC_PATH="${CMAKE_CURRENT_SOURCE_DIR}/static")
sourcemeta_add_default_options(PRIVATE sourcemeta_hydra_httpserver_e2e_stub)

sourcemeta_googletest(NAMESPACE sourcemeta PROJECT hydra NAME httpserver_e2e
  FOLDER "Hydra/HTTP Server"
  SOURCES environment.h httpserver_test.cc)

target_link_libraries(sourcemeta_hydra_httpserver_e2e_unit
  PRIVATE sourcemeta::hydra::httpclient)
target_link_libraries(sourcemeta_hydra_httpserver_e2e_unit
  PRIVATE sourcemeta::core::json)
