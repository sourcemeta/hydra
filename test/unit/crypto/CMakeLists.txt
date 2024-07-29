add_executable(sourcemeta_hydra_crypto_unit uuid_test.cc)
noa_add_default_options(PRIVATE sourcemeta_hydra_crypto_unit)
target_link_libraries(sourcemeta_hydra_crypto_unit
  PRIVATE GTest::gtest GTest::gmock GTest::gtest_main)
target_link_libraries(sourcemeta_hydra_crypto_unit
  PRIVATE sourcemeta::hydra::crypto)
set_target_properties(sourcemeta_hydra_crypto_unit
  PROPERTIES FOLDER "Hydra/Crypto")
gtest_discover_tests(sourcemeta_hydra_crypto_unit)
