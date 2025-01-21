if(NOT Noa_FOUND)
  if(JSONTOOLKIT_INSTALL)
    set(NOA_INSTALL ON CACHE BOOL "enable Noa installation")
  else()
    set(NOA_INSTALL OFF CACHE BOOL "disable Noa installation")
  endif()

  set(NOA_GOOGLETEST ${JSONTOOLKIT_TESTS} CACHE BOOL "GoogleTest")
  set(NOA_GOOGLEBENCHMARK ${JSONTOOLKIT_BENCHMARK} CACHE BOOL "GoogleBenchmark")
  add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/noa")
  set(Noa_FOUND ON)
endif()
