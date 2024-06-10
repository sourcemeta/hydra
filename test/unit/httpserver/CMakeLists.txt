add_executable(sourcemeta_hydra_httpserver_unit logger_test.cc)
noa_add_default_options(PRIVATE sourcemeta_hydra_httpserver_unit)
target_link_libraries(sourcemeta_hydra_httpserver_unit
  PRIVATE GTest::gtest GTest::gmock GTest::gtest_main)
target_link_libraries(sourcemeta_hydra_httpserver_unit
  PRIVATE sourcemeta::hydra::httpserver)
set_target_properties(sourcemeta_hydra_httpserver_unit
  PROPERTIES FOLDER "Hydra/HTTP Server")
gtest_discover_tests(sourcemeta_hydra_httpserver_unit)
