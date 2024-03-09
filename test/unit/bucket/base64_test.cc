#include <gtest/gtest.h>

#include <sourcemeta/hydra/bucket_aws_sigv4.h>

#include <sstream>

// See https://www.base64encode.org

TEST(Bucket_aws_sigv4, base64_encode_foo) {
  std::ostringstream result;
  sourcemeta::hydra::aws_sigv4_base64("foo", result);
  EXPECT_EQ(result.str(), "Zm9v");
}

TEST(Bucket_aws_sigv4, base64_encode_intelligence) {
  std::ostringstream result;
  sourcemeta::hydra::aws_sigv4_base64("intelligence", result);
  EXPECT_EQ(result.str(), "aW50ZWxsaWdlbmNl");
}

TEST(Bucket_aws_sigv4, base64_encode_hello_world) {
  std::ostringstream result;
  sourcemeta::hydra::aws_sigv4_base64("Hello, World!", result);
  EXPECT_EQ(result.str(), "SGVsbG8sIFdvcmxkIQ==");
}
