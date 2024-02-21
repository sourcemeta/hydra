add_executable(sourcemeta_hydra_http_unit
  time_test.cc method_test.cc http_base_url.h
  request_1_1_test.cc stream_1_1_test.cc)
sourcemeta_hydra_add_compile_options(sourcemeta_hydra_http_unit)
target_link_libraries(sourcemeta_hydra_http_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_hydra_http_unit
  PRIVATE sourcemeta::hydra::http)
set_target_properties(sourcemeta_hydra_http_unit
  PROPERTIES FOLDER "Hydra/HTTP")
gtest_discover_tests(sourcemeta_hydra_http_unit)

if(NOA_COMPILER_MSVC)
  target_compile_definitions(sourcemeta_hydra_http_unit
    PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
