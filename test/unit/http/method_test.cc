#include <gtest/gtest.h>

#include <sstream>

#include <sourcemeta/hydra/http.h>

TEST(HTTP_Method, method_get) {
  const sourcemeta::hydra::http::Method method{
      sourcemeta::hydra::http::Method::GET};
  std::ostringstream result;
  result << method;
  EXPECT_EQ(result.str(), "GET");
  EXPECT_EQ(sourcemeta::hydra::http::to_method("GET"), method);
}

TEST(HTTP_Method, method_head) {
  const sourcemeta::hydra::http::Method method{
      sourcemeta::hydra::http::Method::HEAD};
  std::ostringstream result;
  result << method;
  EXPECT_EQ(result.str(), "HEAD");
  EXPECT_EQ(sourcemeta::hydra::http::to_method("HEAD"), method);
}

TEST(HTTP_Method, method_post) {
  const sourcemeta::hydra::http::Method method{
      sourcemeta::hydra::http::Method::POST};
  std::ostringstream result;
  result << method;
  EXPECT_EQ(result.str(), "POST");
  EXPECT_EQ(sourcemeta::hydra::http::to_method("POST"), method);
}

TEST(HTTP_Method, method_put) {
  const sourcemeta::hydra::http::Method method{
      sourcemeta::hydra::http::Method::PUT};
  std::ostringstream result;
  result << method;
  EXPECT_EQ(result.str(), "PUT");
  EXPECT_EQ(sourcemeta::hydra::http::to_method("PUT"), method);
}

TEST(HTTP_Method, method_delete) {
  const sourcemeta::hydra::http::Method method{
      sourcemeta::hydra::http::Method::DELETE};
  std::ostringstream result;
  result << method;
  EXPECT_EQ(result.str(), "DELETE");
  EXPECT_EQ(sourcemeta::hydra::http::to_method("DELETE"), method);
}

TEST(HTTP_Method, method_connect) {
  const sourcemeta::hydra::http::Method method{
      sourcemeta::hydra::http::Method::CONNECT};
  std::ostringstream result;
  result << method;
  EXPECT_EQ(result.str(), "CONNECT");
  EXPECT_EQ(sourcemeta::hydra::http::to_method("CONNECT"), method);
}

TEST(HTTP_Method, method_options) {
  const sourcemeta::hydra::http::Method method{
      sourcemeta::hydra::http::Method::OPTIONS};
  std::ostringstream result;
  result << method;
  EXPECT_EQ(result.str(), "OPTIONS");
  EXPECT_EQ(sourcemeta::hydra::http::to_method("OPTIONS"), method);
}

TEST(HTTP_Method, method_trace) {
  const sourcemeta::hydra::http::Method method{
      sourcemeta::hydra::http::Method::TRACE};
  std::ostringstream result;
  result << method;
  EXPECT_EQ(result.str(), "TRACE");
  EXPECT_EQ(sourcemeta::hydra::http::to_method("TRACE"), method);
}

TEST(HTTP_Method, method_patch) {
  const sourcemeta::hydra::http::Method method{
      sourcemeta::hydra::http::Method::PATCH};
  std::ostringstream result;
  result << method;
  EXPECT_EQ(result.str(), "PATCH");
  EXPECT_EQ(sourcemeta::hydra::http::to_method("PATCH"), method);
}

TEST(HTTP_Method, no_case_detection) {
  EXPECT_THROW(sourcemeta::hydra::http::to_method("get"),
               std::invalid_argument);
  EXPECT_THROW(sourcemeta::hydra::http::to_method("gEt"),
               std::invalid_argument);
}
