add_executable(sourcemeta_hydra_bucket_unit
  fetch_json_test.cc cache_test.cc http_base_url.h)
sourcemeta_hydra_add_compile_options(sourcemeta_hydra_bucket_unit)
target_link_libraries(sourcemeta_hydra_bucket_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_hydra_bucket_unit
  PRIVATE sourcemeta::hydra::bucket)
set_target_properties(sourcemeta_hydra_bucket_unit
  PROPERTIES FOLDER "Hydra/Bucket")
gtest_discover_tests(sourcemeta_hydra_bucket_unit)

if(NOA_COMPILER_MSVC)
  target_compile_definitions(sourcemeta_hydra_bucket_unit
    PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
