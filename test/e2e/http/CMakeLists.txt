sourcemeta_googletest(NAMESPACE sourcemeta PROJECT hydra NAME http_e2e
  FOLDER "Hydra/HTTP"
  SOURCES environment.h request_1_1_test.cc stream_1_1_test.cc)

target_link_libraries(sourcemeta_hydra_http_e2e_unit
  PRIVATE sourcemeta::hydra::http)
target_link_libraries(sourcemeta_hydra_http_e2e_unit
  PRIVATE sourcemeta::core::time)

if(SOURCEMETA_COMPILER_MSVC)
  target_compile_definitions(sourcemeta_hydra_http_e2e_unit
    PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
