#include <gtest/gtest.h>

#include <sstream>

#include <sourcemeta/hydra/http.h>

TEST(HTTP_Status, ok_to_string) {
  std::ostringstream result;
  result << sourcemeta::hydra::http::Status::OK;
  EXPECT_EQ(result.str(), "200 OK");
}

TEST(HTTP_Status, unauthorized_to_string) {
  std::ostringstream result;
  result << sourcemeta::hydra::http::Status::UNAUTHORIZED;
  EXPECT_EQ(result.str(), "401 Unauthorized");
}
