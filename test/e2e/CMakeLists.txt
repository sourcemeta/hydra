add_executable(https_request https_request.cc)
target_link_libraries(https_request PRIVATE CPR::cpr)
set_target_properties(https_request PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF)
add_test(NAME hydra.e2e.https_request COMMAND https_request)

add_executable(http2_request http2_request.cc)
target_link_libraries(http2_request PRIVATE CPR::cpr)
set_target_properties(http2_request PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF)
add_test(NAME hydra.e2e.http2_request COMMAND http2_request)

add_executable(compression_test compression_test.cc)
target_link_libraries(compression_test PRIVATE CPR::cpr)
set_target_properties(compression_test PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF)
add_test(NAME hydra.e2e.compression_test COMMAND compression_test)

add_executable(custom_headers_test custom_headers_test.cc)
target_link_libraries(custom_headers_test PRIVATE CPR::cpr)
set_target_properties(custom_headers_test PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF)
add_test(NAME hydra.e2e.custom_headers_test COMMAND custom_headers_test)

add_executable(post_request_test post_json_test.cc)
target_link_libraries(post_request_test PRIVATE CPR::cpr)
set_target_properties(post_request_test PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF)
add_test(NAME hydra.e2e.post_request_test COMMAND post_request_test)
