#include <gtest/gtest.h>

#include <sourcemeta/hydra/crypto.h>

#include <sstream>

// Try $ echo -n "foo bar" | md5sum
TEST(Crypto_md5, example_string) {
  std::ostringstream result;
  sourcemeta::hydra::md5("foo bar", result);
  EXPECT_EQ(result.str(), "327b6f07435811239bc47e1544353273");
}

// Try $ echo -n "" | md5sum
TEST(Crypto_md5, empty_string) {
  std::ostringstream result;
  sourcemeta::hydra::md5("", result);
  EXPECT_EQ(result.str(), "d41d8cd98f00b204e9800998ecf8427e");
}
