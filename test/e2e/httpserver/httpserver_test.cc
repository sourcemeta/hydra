#include <gtest/gtest.h>

#include <sourcemeta/hydra/httpclient.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <algorithm>
#include <chrono>
#include <sstream>

#include "environment.h"

TEST(e2e_HTTP_Server, echo_get) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo"};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture();
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_EQ(response.header("content-type").value(), "application/json");
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(response.body());
  EXPECT_TRUE(document.is_object());
  EXPECT_TRUE(document.defines("method"));
  EXPECT_TRUE(document.at("method").is_string());
  EXPECT_EQ(document.at("method").to_string(), "GET");
  EXPECT_TRUE(document.defines("path"));
  EXPECT_TRUE(document.at("path").is_string());
  EXPECT_EQ(document.at("path").to_string(), "/echo");
}

TEST(e2e_HTTP_Server, echo_head) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo"};
  request.method(sourcemeta::hydra::http::Method::HEAD);
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.empty());
}

TEST(e2e_HTTP_Server, echo_post) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo"};
  request.method(sourcemeta::hydra::http::Method::POST);
  request.capture();
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_EQ(response.header("content-type").value(), "application/json");
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(response.body());
  EXPECT_TRUE(document.is_object());
  EXPECT_TRUE(document.defines("method"));
  EXPECT_TRUE(document.at("method").is_string());
  EXPECT_EQ(document.at("method").to_string(), "POST");
  EXPECT_TRUE(document.defines("path"));
  EXPECT_TRUE(document.at("path").is_string());
  EXPECT_EQ(document.at("path").to_string(), "/echo");
}

TEST(e2e_HTTP_Server, echo_put) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo"};
  request.method(sourcemeta::hydra::http::Method::PUT);
  request.capture();
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_EQ(response.header("content-type").value(), "application/json");
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(response.body());
  EXPECT_TRUE(document.is_object());
  EXPECT_TRUE(document.defines("method"));
  EXPECT_TRUE(document.at("method").is_string());
  EXPECT_EQ(document.at("method").to_string(), "PUT");
  EXPECT_TRUE(document.defines("path"));
  EXPECT_TRUE(document.at("path").is_string());
  EXPECT_EQ(document.at("path").to_string(), "/echo");
}

TEST(e2e_HTTP_Server, echo_delete) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo"};
  request.method(sourcemeta::hydra::http::Method::DELETE);
  request.capture();
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_EQ(response.header("content-type").value(), "application/json");
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(response.body());
  EXPECT_TRUE(document.is_object());
  EXPECT_TRUE(document.defines("method"));
  EXPECT_TRUE(document.at("method").is_string());
  EXPECT_EQ(document.at("method").to_string(), "DELETE");
  EXPECT_TRUE(document.defines("path"));
  EXPECT_TRUE(document.at("path").is_string());
  EXPECT_EQ(document.at("path").to_string(), "/echo");
}

TEST(e2e_HTTP_Server, echo_connect) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo"};
  request.method(sourcemeta::hydra::http::Method::CONNECT);
  request.capture();
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_EQ(response.header("content-type").value(), "application/json");
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(response.body());
  EXPECT_TRUE(document.is_object());
  EXPECT_TRUE(document.defines("method"));
  EXPECT_TRUE(document.at("method").is_string());
  EXPECT_EQ(document.at("method").to_string(), "CONNECT");
  EXPECT_TRUE(document.defines("path"));
  EXPECT_TRUE(document.at("path").is_string());
  EXPECT_EQ(document.at("path").to_string(), "/echo");
}

TEST(e2e_HTTP_Server, echo_options) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo"};
  request.method(sourcemeta::hydra::http::Method::OPTIONS);
  request.capture();
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_EQ(response.header("content-type").value(), "application/json");
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(response.body());
  EXPECT_TRUE(document.is_object());
  EXPECT_TRUE(document.defines("method"));
  EXPECT_TRUE(document.at("method").is_string());
  EXPECT_EQ(document.at("method").to_string(), "OPTIONS");
  EXPECT_TRUE(document.defines("path"));
  EXPECT_TRUE(document.at("path").is_string());
  EXPECT_EQ(document.at("path").to_string(), "/echo");
}

TEST(e2e_HTTP_Server, echo_trace) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo"};
  request.method(sourcemeta::hydra::http::Method::TRACE);
  request.capture();
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_EQ(response.header("content-type").value(), "application/json");
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(response.body());
  EXPECT_TRUE(document.is_object());
  EXPECT_TRUE(document.defines("method"));
  EXPECT_TRUE(document.at("method").is_string());
  EXPECT_EQ(document.at("method").to_string(), "TRACE");
  EXPECT_TRUE(document.defines("path"));
  EXPECT_TRUE(document.at("path").is_string());
  EXPECT_EQ(document.at("path").to_string(), "/echo");
}

TEST(e2e_HTTP_Server, echo_patch) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo"};
  request.method(sourcemeta::hydra::http::Method::PATCH);
  request.capture();
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_EQ(response.header("content-type").value(), "application/json");
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(response.body());
  EXPECT_TRUE(document.is_object());
  EXPECT_TRUE(document.defines("method"));
  EXPECT_TRUE(document.at("method").is_string());
  EXPECT_EQ(document.at("method").to_string(), "PATCH");
  EXPECT_TRUE(document.defines("path"));
  EXPECT_TRUE(document.at("path").is_string());
  EXPECT_EQ(document.at("path").to_string(), "/echo");
}

TEST(e2e_HTTP_Server, echo_get_with_query) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo?foo=bar"};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture();
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_EQ(response.header("content-type").value(), "application/json");
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(response.body());
  EXPECT_TRUE(document.is_object());
  EXPECT_TRUE(document.defines("method"));
  EXPECT_TRUE(document.at("method").is_string());
  EXPECT_EQ(document.at("method").to_string(), "GET");
  EXPECT_TRUE(document.defines("path"));
  EXPECT_TRUE(document.at("path").is_string());
  EXPECT_EQ(document.at("path").to_string(), "/echo");
}

TEST(e2e_HTTP_Server, otherwise_root_get) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()}};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture();
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(),
            sourcemeta::hydra::http::Status::NOT_IMPLEMENTED);
  EXPECT_TRUE(response.empty());
}

TEST(e2e_HTTP_Server, otherwise_foo_bar_post) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/foo/bar"};
  request.method(sourcemeta::hydra::http::Method::POST);
  request.capture();
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(),
            sourcemeta::hydra::http::Status::NOT_IMPLEMENTED);
  EXPECT_TRUE(response.empty());
}

TEST(e2e_HTTP_Server, throw_test) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/throw"};
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::BAD_REQUEST);
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "Crash!");
}

TEST(e2e_HTTP_Server, echo_x_foo_without) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo-x-foo"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.header("x-foo").has_value());
  EXPECT_TRUE(response.empty());
}

TEST(e2e_HTTP_Server, echo_x_foo_with) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo-x-foo"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("x-foo", "hello");
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("x-foo").has_value());
  EXPECT_EQ(response.header("x-foo").value(), "hello");
  EXPECT_TRUE(response.empty());
}

TEST(e2e_HTTP_Server, echo_query_foo_without) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo-query-foo"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.header("x-foo").has_value());
  EXPECT_TRUE(response.empty());
}

TEST(e2e_HTTP_Server, echo_query_foo_other) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo-query-foo?bar=baz"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.header("x-foo").has_value());
  EXPECT_TRUE(response.empty());
}

TEST(e2e_HTTP_Server, echo_query_foo_with) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/echo-query-foo?foo=hello"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("x-foo").has_value());
  EXPECT_EQ(response.header("x-foo").value(), "hello");
  EXPECT_TRUE(response.empty());
}

TEST(e2e_HTTP_Server, parameters_foo_bar_baz) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/parameters/foo/bar/baz"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "foo bar baz");
}

TEST(e2e_HTTP_Server, parameters_one_two_three) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/parameters/one/two/three"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "one two three");
}

TEST(e2e_HTTP_Server, encodings_gzip_brotli) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/encodings"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("Accept-Encoding", "gzip, brotli");
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-type").has_value());
  EXPECT_EQ(response.header("content-type").value(), "application/json");
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(response.body());
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.at(0).is_string());
  EXPECT_TRUE(document.at(1).is_string());
  EXPECT_EQ(document.at(0).to_string(), "gzip");
  EXPECT_EQ(document.at(1).to_string(), "brotli");
}

TEST(e2e_HTTP_Server, force_gzip_default) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/force-gzip"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-encoding").has_value());
  EXPECT_EQ(response.header("content-encoding").value(), "gzip");
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "I am compressed");
}

TEST(e2e_HTTP_Server, force_gzip_non_matching_accept_encoding) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/force-gzip"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("Accept-Encoding", "brotli");
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-encoding").has_value());
  EXPECT_EQ(response.header("content-encoding").value(), "gzip");
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "I am compressed");
}

TEST(e2e_HTTP_Server, gzip_by_default) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/parameters/foo/bar/baz"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-encoding").has_value());
  EXPECT_EQ(response.header("content-encoding").value(), "gzip");
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "foo bar baz");
}

TEST(e2e_HTTP_Server, accept_encoding_gzip) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/parameters/foo/bar/baz"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("Accept-Encoding", "gzip");
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-encoding").has_value());
  EXPECT_EQ(response.header("content-encoding").value(), "gzip");
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "foo bar baz");
}

TEST(e2e_HTTP_Server, accept_encoding_as_fallback) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/parameters/foo/bar/baz"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("Accept-Encoding", "xxx, yyy, gzip");
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-encoding").has_value());
  EXPECT_EQ(response.header("content-encoding").value(), "gzip");
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "foo bar baz");
}

TEST(e2e_HTTP_Server, accept_encoding_as_fallback_with_quality_values) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/parameters/foo/bar/baz"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("Accept-Encoding", "xxx;q=1.0, gzip;q=0.5, yyy;0.8");
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-encoding").has_value());
  EXPECT_EQ(response.header("content-encoding").value(), "gzip");
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "foo bar baz");
}

TEST(e2e_HTTP_Server, accept_encoding_identity) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/parameters/foo/bar/baz"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("Accept-Encoding", "identity");
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.header("content-encoding").has_value());
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "foo bar baz");
}

TEST(e2e_HTTP_Server, accept_encoding_gzip_identity) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/parameters/foo/bar/baz"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("Accept-Encoding", "gzip, identity");
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response.header("content-encoding").has_value());
  EXPECT_EQ(response.header("content-encoding").value(), "gzip");
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "foo bar baz");
}

TEST(e2e_HTTP_Server, accept_encoding_gzip_identity_with_quality_values) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/parameters/foo/bar/baz"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("Accept-Encoding", "gzip;q=0.1, identity;q=0.8");
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.header("content-encoding").has_value());
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "foo bar baz");
}

TEST(e2e_HTTP_Server, accept_encoding_prohibit_gzip) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/parameters/foo/bar/baz"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("Accept-Encoding", "gzip;q=0");
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.header("content-encoding").has_value());
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "foo bar baz");
}

TEST(e2e_HTTP_Server, accept_encoding_deny_everything) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/parameters/foo/bar/baz"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("Accept-Encoding", "*;q=0");
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::NOT_ACCEPTABLE);
  EXPECT_FALSE(response.header("content-encoding").has_value());
  EXPECT_TRUE(response.empty());
}

TEST(e2e_HTTP_Server, accept_encoding_deny_identity) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/parameters/foo/bar/baz"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("Accept-Encoding", "identity;q=0");
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::NOT_ACCEPTABLE);
  EXPECT_FALSE(response.header("content-encoding").has_value());
  EXPECT_TRUE(response.empty());
}

TEST(e2e_HTTP_Server, accept_encoding_deny_unknown) {
  sourcemeta::hydra::http::ClientRequest request{
      std::string{HTTPSERVER_BASE_URL()} + "/parameters/foo/bar/baz"};
  request.capture();
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("Accept-Encoding", "foo;q=0");
  sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(response.header("content-encoding").has_value());
  EXPECT_FALSE(response.empty());
  std::ostringstream result;
  std::copy(
      std::istreambuf_iterator<std::ostringstream::char_type>(response.body()),
      std::istreambuf_iterator<std::ostringstream::char_type>(),
      std::ostreambuf_iterator<std::ostringstream::char_type>(result));
  EXPECT_EQ(result.str(), "foo bar baz");
}

TEST(e2e_HTTP_Server, cache_me_if_modified_since_equal) {
  sourcemeta::hydra::http::ClientRequest request_1{
      std::string{HTTPSERVER_BASE_URL()} + "/cache-me"};
  request_1.capture();
  request_1.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::ClientResponse response_1{request_1.send().get()};
  EXPECT_EQ(response_1.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response_1.header("last-modified").has_value());
  EXPECT_FALSE(response_1.empty());
  std::ostringstream result_1;
  std::copy(std::istreambuf_iterator<std::ostringstream::char_type>(
                response_1.body()),
            std::istreambuf_iterator<std::ostringstream::char_type>(),
            std::ostreambuf_iterator<std::ostringstream::char_type>(result_1));
  EXPECT_EQ(result_1.str(), "Cache me!");

  sourcemeta::hydra::http::ClientRequest request_2{
      std::string{HTTPSERVER_BASE_URL()} + "/cache-me"};
  request_2.capture();
  request_2.method(sourcemeta::hydra::http::Method::GET);
  request_2.header("If-Modified-Since",
                   response_1.header("last-modified").value());
  sourcemeta::hydra::http::ClientResponse response_2{request_2.send().get()};
  EXPECT_EQ(response_2.status(), sourcemeta::hydra::http::Status::NOT_MODIFIED);
  EXPECT_FALSE(response_2.header("last-modified").has_value());
  EXPECT_TRUE(response_2.empty());
}

TEST(e2e_HTTP_Server, cache_me_if_modified_since_greater) {
  sourcemeta::hydra::http::ClientRequest request_1{
      std::string{HTTPSERVER_BASE_URL()} + "/cache-me"};
  request_1.capture();
  request_1.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::ClientResponse response_1{request_1.send().get()};
  EXPECT_EQ(response_1.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response_1.header("last-modified").has_value());
  EXPECT_FALSE(response_1.empty());
  std::ostringstream result_1;
  std::copy(std::istreambuf_iterator<std::ostringstream::char_type>(
                response_1.body()),
            std::istreambuf_iterator<std::ostringstream::char_type>(),
            std::ostreambuf_iterator<std::ostringstream::char_type>(result_1));
  EXPECT_EQ(result_1.str(), "Cache me!");

  auto timestamp{sourcemeta::hydra::http::from_gmt(
      response_1.header("last-modified").value())};
  timestamp += std::chrono::hours{1};

  sourcemeta::hydra::http::ClientRequest request_2{
      std::string{HTTPSERVER_BASE_URL()} + "/cache-me"};
  request_2.capture();
  request_2.method(sourcemeta::hydra::http::Method::GET);
  request_2.header("If-Modified-Since",
                   sourcemeta::hydra::http::to_gmt(timestamp));
  sourcemeta::hydra::http::ClientResponse response_2{request_2.send().get()};
  EXPECT_EQ(response_2.status(), sourcemeta::hydra::http::Status::NOT_MODIFIED);
  EXPECT_FALSE(response_2.header("last-modified").has_value());
  EXPECT_TRUE(response_2.empty());
}

TEST(e2e_HTTP_Server, cache_me_if_modified_since_less) {
  sourcemeta::hydra::http::ClientRequest request_1{
      std::string{HTTPSERVER_BASE_URL()} + "/cache-me"};
  request_1.capture();
  request_1.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::ClientResponse response_1{request_1.send().get()};
  EXPECT_EQ(response_1.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response_1.header("last-modified").has_value());
  EXPECT_FALSE(response_1.empty());
  std::ostringstream result_1;
  std::copy(std::istreambuf_iterator<std::ostringstream::char_type>(
                response_1.body()),
            std::istreambuf_iterator<std::ostringstream::char_type>(),
            std::ostreambuf_iterator<std::ostringstream::char_type>(result_1));
  EXPECT_EQ(result_1.str(), "Cache me!");

  auto timestamp{sourcemeta::hydra::http::from_gmt(
      response_1.header("last-modified").value())};
  timestamp -= std::chrono::hours{1};

  sourcemeta::hydra::http::ClientRequest request_2{
      std::string{HTTPSERVER_BASE_URL()} + "/cache-me"};
  request_2.capture();
  request_2.method(sourcemeta::hydra::http::Method::GET);
  request_2.header("If-Modified-Since",
                   sourcemeta::hydra::http::to_gmt(timestamp));
  sourcemeta::hydra::http::ClientResponse response_2{request_2.send().get()};
  EXPECT_EQ(response_2.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response_2.header("last-modified").has_value());
  EXPECT_FALSE(response_2.empty());
  std::ostringstream result_2;
  std::copy(std::istreambuf_iterator<std::ostringstream::char_type>(
                response_2.body()),
            std::istreambuf_iterator<std::ostringstream::char_type>(),
            std::ostreambuf_iterator<std::ostringstream::char_type>(result_2));
  EXPECT_EQ(result_2.str(), "Cache me!");
}

TEST(e2e_HTTP_Server, cache_me_if_modified_since_equal_post) {
  sourcemeta::hydra::http::ClientRequest request_1{
      std::string{HTTPSERVER_BASE_URL()} + "/cache-me"};
  request_1.capture();
  request_1.method(sourcemeta::hydra::http::Method::POST);
  sourcemeta::hydra::http::ClientResponse response_1{request_1.send().get()};
  EXPECT_EQ(response_1.status(), sourcemeta::hydra::http::Status::OK);
  EXPECT_TRUE(response_1.header("last-modified").has_value());
  EXPECT_FALSE(response_1.empty());
  std::ostringstream result_1;
  std::copy(std::istreambuf_iterator<std::ostringstream::char_type>(
                response_1.body()),
            std::istreambuf_iterator<std::ostringstream::char_type>(),
            std::ostreambuf_iterator<std::ostringstream::char_type>(result_1));
  EXPECT_EQ(result_1.str(), "Cache me!");

  sourcemeta::hydra::http::ClientRequest request_2{
      std::string{HTTPSERVER_BASE_URL()} + "/cache-me"};
  request_2.capture();
  request_2.method(sourcemeta::hydra::http::Method::POST);
  request_2.header("If-Modified-Since",
                   response_1.header("last-modified").value());
  sourcemeta::hydra::http::ClientResponse response_2{request_2.send().get()};
  EXPECT_EQ(response_2.status(), sourcemeta::hydra::http::Status::OK);
}
