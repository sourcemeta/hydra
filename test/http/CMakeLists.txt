# TODO: Add HTTP/2 tests

add_executable(sourcemeta_hydra_http_unit
  request_1_1_test.cc)
sourcemeta_hydra_add_compile_options(sourcemeta_hydra_http_unit)
target_compile_definitions(sourcemeta_hydra_http_unit PRIVATE
  BASE_URL="http://localhost:9999")
target_link_libraries(sourcemeta_hydra_http_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_hydra_http_unit
  PRIVATE sourcemeta::hydra::http)
set_target_properties(sourcemeta_hydra_http_unit
  PROPERTIES FOLDER "Hydra/HTTP")
gtest_discover_tests(sourcemeta_hydra_http_unit)
