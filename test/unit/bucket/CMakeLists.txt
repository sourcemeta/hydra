sourcemeta_googletest(NAMESPACE sourcemeta PROJECT hydra NAME bucket
  FOLDER "Hydra/Bucket"
  SOURCES cache_test.cc datastamp_test.cc iso8601_test.cc aws_sigv4_test.cc)

target_link_libraries(sourcemeta_hydra_bucket_unit
  PRIVATE sourcemeta::hydra::bucket)
target_link_libraries(sourcemeta_hydra_bucket_unit
  PRIVATE sourcemeta::hydra::crypto)
