add_executable(sourcemeta_hydra_httpclient_e2e
  environment.h request_1_1_test.cc stream_1_1_test.cc)
noa_add_default_options(PRIVATE sourcemeta_hydra_httpclient_e2e)
target_link_libraries(sourcemeta_hydra_httpclient_e2e
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_hydra_httpclient_e2e
  PRIVATE sourcemeta::hydra::httpclient)
set_target_properties(sourcemeta_hydra_httpclient_e2e
  PROPERTIES FOLDER "Hydra/HTTP Client")
gtest_discover_tests(sourcemeta_hydra_httpclient_e2e)

if(NOA_COMPILER_MSVC)
  target_compile_definitions(sourcemeta_hydra_httpclient_e2e
    PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
