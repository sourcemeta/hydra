add_executable(sourcemeta_hydra_http_unit
  time_test.cc status_test.cc method_test.cc
  header_test.cc mime_test.cc)
noa_add_default_options(PRIVATE sourcemeta_hydra_http_unit)
target_link_libraries(sourcemeta_hydra_http_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_hydra_http_unit
  PRIVATE sourcemeta::hydra::http)
set_target_properties(sourcemeta_hydra_http_unit
  PROPERTIES FOLDER "Hydra/HTTP")
gtest_discover_tests(sourcemeta_hydra_http_unit)
