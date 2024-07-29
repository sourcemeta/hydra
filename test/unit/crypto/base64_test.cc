#include <gtest/gtest.h>

#include <sourcemeta/hydra/crypto.h>

#include <sstream>

// See https://www.base64encode.org

TEST(Crypto_base64, encode_foo) {
  std::ostringstream result;
  sourcemeta::hydra::base64_encode("foo", result);
  EXPECT_EQ(result.str(), "Zm9v");
}

TEST(Crypto_base64, encode_intelligence) {
  std::ostringstream result;
  sourcemeta::hydra::base64_encode("intelligence", result);
  EXPECT_EQ(result.str(), "aW50ZWxsaWdlbmNl");
}

TEST(Crypto_base64, encode_hello_world) {
  std::ostringstream result;
  sourcemeta::hydra::base64_encode("Hello, World!", result);
  EXPECT_EQ(result.str(), "SGVsbG8sIFdvcmxkIQ==");
}
