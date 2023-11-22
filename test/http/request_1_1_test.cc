#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>

#include <gtest/gtest.h>
#include <sourcemeta/hydra/http.h>

static auto body(sourcemeta::hydra::http::Response &response) -> std::string {
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  return result.str();
}

TEST(HTTP_Request_1_1, invalid_url) {
  sourcemeta::hydra::http::Request request{"foobarbaz"};
  EXPECT_THROW(request.send().get(), sourcemeta::hydra::http::Error);
}

TEST(HTTP_Request_1_1, GET_root) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
}

TEST(HTTP_Request_1_1, HEAD_root) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::HEAD);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.empty());
}

TEST(HTTP_Request_1_1, POST_root) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::POST);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED POST /");
}

TEST(HTTP_Request_1_1, PUT_root) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::PUT);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED PUT /");
}

TEST(HTTP_Request_1_1, DELETE_root) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::DELETE);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED DELETE /");
}

TEST(HTTP_Request_1_1, OPTIONS_root) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::OPTIONS);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED OPTIONS /");
}

TEST(HTTP_Request_1_1, TRACE_root) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::TRACE);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED TRACE /");
}

TEST(HTTP_Request_1_1, PATCH_root) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::PATCH);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED PATCH /");
}

TEST(HTTP_Request_1_1, GET_root_foo_bar) {
  sourcemeta::hydra::http::Request request{std::string{BASE_URL} + "/foo/bar"};
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /foo/bar");
}

TEST(HTTP_Request_1_1, GET_root_custom_code_string) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("X-Code", "400");
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::BAD_REQUEST);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
}

TEST(HTTP_Request_1_1, GET_root_custom_code_integer) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("X-Code", 400);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::BAD_REQUEST);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
}

TEST(HTTP_Request_1_1, GET_root_response_content_type_no_capture) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_FALSE(response.header("content-type").has_value());
}

TEST(HTTP_Request_1_1, GET_root_response_content_type_capture) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture("content-type");
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_EQ(response.header("content-type").value(), "text/plain");
}

TEST(HTTP_Request_1_1, GET_root_missing_header_with_capture) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture("x-foo-bar");
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_FALSE(response.header("x-foo-bar").has_value());
}

TEST(HTTP_Request_1_1, GET_root_multiple_captures_match) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture("content-type");
  request.capture("content-length");
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_TRUE(response.header("content-length").has_value());
  EXPECT_EQ(response.header("content-type").value(), "text/plain");
  EXPECT_EQ(response.header("content-length").value(), "14");
}

TEST(HTTP_Request_1_1, GET_root_multiple_captures_partial_match) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture("content-type");
  request.capture("x-foo-bar");
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_FALSE(response.header("x-foo-bar").has_value());
  EXPECT_EQ(response.header("content-type").value(), "text/plain");
}

TEST(HTTP_Request_1_1, GET_root_multiple_captures_match_initializer_list) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture({"content-type", "content-length"});
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_TRUE(response.header("content-length").has_value());
  EXPECT_EQ(response.header("content-type").value(), "text/plain");
  EXPECT_EQ(response.header("content-length").value(), "14");
}

TEST(HTTP_Request_1_1,
     GET_root_multiple_captures_partial_match_initializer_list) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture({"content-type", "x-foo-bar"});
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_FALSE(response.header("x-foo-bar").has_value());
  EXPECT_EQ(response.header("content-type").value(), "text/plain");
}

TEST(HTTP_Request_1_1, GET_root_request_header_echo) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("x-foo-bar", "foo");
  request.capture("x-x-foo-bar");
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_TRUE(response.header("x-x-foo-bar").has_value());
  EXPECT_EQ(response.header("x-x-foo-bar").value(), "foo");
}

TEST(HTTP_Request_1_1, GET_root_request_header_mixed_case_echo) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("X-Foo-Bar", "foo");
  request.capture("x-x-foo-bar");
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_TRUE(response.header("x-x-foo-bar").has_value());
  EXPECT_EQ(response.header("x-x-foo-bar").value(), "foo");
}
