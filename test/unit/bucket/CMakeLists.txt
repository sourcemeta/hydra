add_executable(sourcemeta_hydra_bucket_unit
  cache_test.cc sha256_test.cc hmac_sha256_test.cc
  datastamp_test.cc iso8601_test.cc aws_sigv4_test.cc)
noa_add_default_options(PRIVATE sourcemeta_hydra_bucket_unit)
target_link_libraries(sourcemeta_hydra_bucket_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_hydra_bucket_unit
  PRIVATE sourcemeta::hydra::bucket)
target_link_libraries(sourcemeta_hydra_bucket_unit
  PRIVATE sourcemeta::hydra::crypto)
set_target_properties(sourcemeta_hydra_bucket_unit
  PROPERTIES FOLDER "Hydra/Bucket")
gtest_discover_tests(sourcemeta_hydra_bucket_unit)
