add_executable(sourcemeta_hydra_httpserver_e2e_stub stub.cc)
target_link_libraries(sourcemeta_hydra_httpserver_e2e_stub PRIVATE
  sourcemeta::hydra::httpserver)
target_link_libraries(sourcemeta_hydra_httpserver_e2e_stub PRIVATE
  sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_hydra_httpserver_e2e_stub PRIVATE
  sourcemeta::jsontoolkit::jsonschema)
target_compile_definitions(sourcemeta_hydra_httpserver_e2e_stub PRIVATE
  STATIC_PATH="${CMAKE_CURRENT_SOURCE_DIR}/static")
noa_add_default_options(PRIVATE sourcemeta_hydra_httpserver_e2e_stub)

add_executable(sourcemeta_hydra_httpserver_e2e
  environment.h httpserver_test.cc)
noa_add_default_options(PRIVATE sourcemeta_hydra_httpserver_e2e)
target_link_libraries(sourcemeta_hydra_httpserver_e2e
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_hydra_httpserver_e2e
  PRIVATE sourcemeta::hydra::httpclient)
target_link_libraries(sourcemeta_hydra_httpserver_e2e
  PRIVATE sourcemeta::jsontoolkit::json)
set_target_properties(sourcemeta_hydra_httpserver_e2e
  PROPERTIES FOLDER "Hydra/HTTP server")
gtest_discover_tests(sourcemeta_hydra_httpserver_e2e)
