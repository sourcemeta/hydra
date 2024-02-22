#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <ctime>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <sourcemeta/hydra/http.h>

#include "http_base_url.h"

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
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
}

TEST(HTTP_Request_1_1, HEAD_root) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::HEAD);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.empty());
}

TEST(HTTP_Request_1_1, POST_root) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::POST);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED POST /");
}

TEST(HTTP_Request_1_1, PUT_root) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::PUT);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED PUT /");
}

TEST(HTTP_Request_1_1, DELETE_root) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::DELETE);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED DELETE /");
}

TEST(HTTP_Request_1_1, OPTIONS_root) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::OPTIONS);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED OPTIONS /");
}

TEST(HTTP_Request_1_1, TRACE_root) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::TRACE);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED TRACE /");
}

TEST(HTTP_Request_1_1, PATCH_root) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::PATCH);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED PATCH /");
}

TEST(HTTP_Request_1_1, GET_root_foo_bar) {
  sourcemeta::hydra::http::Request request{std::string{HTTP_BASE_URL()} +
                                           "/foo/bar"};
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /foo/bar");
}

TEST(HTTP_Request_1_1, GET_root_custom_code_string) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("X-Code", "400");
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::BAD_REQUEST);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
}

TEST(HTTP_Request_1_1, GET_root_custom_code_integer) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("X-Code", 400);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::BAD_REQUEST);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
}

TEST(HTTP_Request_1_1, GET_root_response_content_type_no_capture) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_FALSE(response.header("content-type").has_value());
}

TEST(HTTP_Request_1_1, GET_root_response_content_type_capture) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture("content-type");
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_EQ(response.header("content-type").value(), "text/plain");
}

TEST(HTTP_Request_1_1, GET_root_response_content_type_capture_all) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture();
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_TRUE(response.header("content-type").has_value());
}

TEST(HTTP_Request_1_1, GET_root_missing_header_with_capture) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture("x-foo-bar");
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_FALSE(response.header("x-foo-bar").has_value());
}

TEST(HTTP_Request_1_1, GET_root_multiple_captures_match) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
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
}

TEST(HTTP_Request_1_1, GET_root_multiple_captures_partial_match) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
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
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture({"content-type", "content-length"});
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_TRUE(response.header("content-length").has_value());
  EXPECT_EQ(response.header("content-type").value(), "text/plain");
}

TEST(HTTP_Request_1_1,
     GET_root_multiple_captures_partial_match_initializer_list) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
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
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
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
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
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

TEST(HTTP_Request_1_1, GET_root_multiple_times) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);

  sourcemeta::hydra::http::Response response_1{request.send().get()};
  EXPECT_EQ(response_1.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response_1.empty());
  EXPECT_EQ(body(response_1), "RECEIVED GET /");

  sourcemeta::hydra::http::Response response_2{request.send().get()};
  EXPECT_EQ(response_2.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response_2.empty());
  EXPECT_EQ(body(response_2), "RECEIVED GET /");
}

TEST(HTTP_Request_1_1, GET_root_move) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::Request new_request{std::move(request)};
  sourcemeta::hydra::http::Response response{new_request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  EXPECT_EQ(body(response), "RECEIVED GET /");
}

TEST(HTTP_Request_1_1, GET_root_response_headers_capture_none) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  std::vector<std::string> headers;
  for (const auto &[key, value] : response.headers()) {
    headers.push_back(key + " " + value);
  }

  EXPECT_TRUE(headers.empty());
}

TEST(HTTP_Request_1_1, GET_root_response_headers_capture_one) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture("content-type");
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  std::vector<std::string> headers;
  for (const auto &[key, value] : response.headers()) {
    headers.push_back(key + " " + value);
  }

  EXPECT_EQ(headers.size(), 1);
  EXPECT_EQ(headers.at(0), "content-type text/plain");
}

TEST(HTTP_Request_1_1, GET_root_response_headers_capture_all) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture();
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  std::map<std::string, std::string> headers;
  for (const auto &[key, value] : response.headers()) {
    headers.emplace(key, value);
  }

  EXPECT_TRUE(headers.contains("content-type"));
  EXPECT_TRUE(headers.contains("content-length"));
}

TEST(HTTP_Request_1_1, GET_root_response_headers_capture_all_aws_sigv4_s3) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.aws_sigv4("s3", "us-east-1", "1234", "secret");
  request.capture();
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  std::map<std::string, std::string> headers;
  for (const auto &[key, value] : response.headers()) {
    headers.emplace(key, value);
  }

  EXPECT_TRUE(headers.contains("x-authorization"));
  EXPECT_TRUE(headers.contains("x-x-amz-date"));
  EXPECT_TRUE(headers.contains("x-host"));

  // The empty SHA
  EXPECT_EQ(headers.at("x-host"), HTTP_BASE_URL());
}

TEST(HTTP_Request_1_1, GET_root_response_header_last_modified_gmt) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture("last-modified");
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);

  const auto last_modified{response.header_gmt("last-modified")};
  EXPECT_TRUE(last_modified.has_value());

  std::tm parts = {};
  parts.tm_year = 115;
  parts.tm_mon = 9;
  parts.tm_mday = 21;
  parts.tm_hour = 11;
  parts.tm_min = 28;
  parts.tm_sec = 0;
  parts.tm_isdst = 0;

#if defined(_MSC_VER)
  const auto expected{
      std::chrono::system_clock::from_time_t(_mkgmtime(&parts))};
#else
  const auto expected{std::chrono::system_clock::from_time_t(timegm(&parts))};
#endif

  EXPECT_EQ(last_modified.value(), expected);
}

TEST(HTTP_Request_1_1, GET_root_response_header_gmt_invalid) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture("content-type");
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_THROW(response.header_gmt("content-type"), std::invalid_argument);
}

TEST(HTTP_Request_1_1, GET_root_response_header_gmt_missing) {
  sourcemeta::hydra::http::Request request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  const auto last_modified{response.header_gmt("last-modified")};
  EXPECT_FALSE(last_modified.has_value());
}
