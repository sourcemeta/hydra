sourcemeta_googletest(NAMESPACE sourcemeta PROJECT hydra NAME crypto
  FOLDER "Hydra/Crypto"
  SOURCES uuid_test.cc base64_test.cc
    md5_test.cc sha256_test.cc hmac_sha256_test.cc)

target_link_libraries(sourcemeta_hydra_crypto_unit
  PRIVATE sourcemeta::hydra::crypto)
