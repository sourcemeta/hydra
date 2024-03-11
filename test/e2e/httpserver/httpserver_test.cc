#include <gtest/gtest.h>

#include <sourcemeta/hydra/httpclient.h>
#include <sourcemeta/jsontoolkit/json.h>

#include "environment.h"

// TODO: Test request headers
// TODO: Test response headers
// TODO: Test response status codes
// TODO: Test "otherwise" handler
// TODO: Test default "otherwise" handler
// TODO: Test a handler that throws
// TODO: Test default error handler
// TODO: Test responding with no body

// TODO: Test /echo with all other methods
TEST(e2e_HTTP_Server, echo_get) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo"};
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(response.body());
  EXPECT_TRUE(document.is_object());
  EXPECT_TRUE(document.defines("method"));
  EXPECT_TRUE(document.at("method").is_string());
  EXPECT_EQ(document.at("method").to_string(), "GET");
}
