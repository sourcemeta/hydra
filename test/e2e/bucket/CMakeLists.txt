sourcemeta_googletest(NAMESPACE sourcemeta PROJECT hydra NAME bucket_e2e
  FOLDER "Hydra/Bucket"
  SOURCES environment.h fetch_json_test.cc
  fetch_or_upsert_test.cc upsert_json_test.cc)

target_link_libraries(sourcemeta_hydra_bucket_e2e_unit
  PRIVATE sourcemeta::hydra::bucket)
target_link_libraries(sourcemeta_hydra_bucket_e2e_unit
  PRIVATE sourcemeta::core::json)

if(SOURCEMETA_COMPILER_MSVC)
  target_compile_definitions(sourcemeta_hydra_bucket_e2e_unit
    PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
