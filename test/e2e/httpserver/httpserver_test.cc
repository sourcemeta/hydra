#include <gtest/gtest.h>

#include <sourcemeta/hydra/httpclient.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <algorithm>
#include <sstream>

#include "environment.h"

// TODO: Test request headers

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
