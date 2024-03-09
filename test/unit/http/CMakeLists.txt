add_executable(sourcemeta_hydra_http_unit
  time_test.cc status_test.cc method_test.cc)
sourcemeta_hydra_add_compile_options(sourcemeta_hydra_http_unit)
target_link_libraries(sourcemeta_hydra_http_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_hydra_http_unit
  PRIVATE sourcemeta::hydra::http)
set_target_properties(sourcemeta_hydra_http_unit
  PROPERTIES FOLDER "Hydra/HTTP")
gtest_discover_tests(sourcemeta_hydra_http_unit)
