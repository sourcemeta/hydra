add_executable(sourcemeta_hydra_bucket_e2e
  environment.h fetch_json_test.cc
  fetch_or_upsert_test.cc upsert_json_test.cc)

noa_add_default_options(PRIVATE sourcemeta_hydra_bucket_e2e)
target_link_libraries(sourcemeta_hydra_bucket_e2e
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_hydra_bucket_e2e
  PRIVATE sourcemeta::hydra::bucket)
target_link_libraries(sourcemeta_hydra_bucket_e2e
  PRIVATE sourcemeta::jsontoolkit::json)
set_target_properties(sourcemeta_hydra_bucket_e2e
  PROPERTIES FOLDER "Hydra/Bucket")
gtest_discover_tests(sourcemeta_hydra_bucket_e2e)

if(NOA_COMPILER_MSVC)
  target_compile_definitions(sourcemeta_hydra_bucket_e2e
    PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
