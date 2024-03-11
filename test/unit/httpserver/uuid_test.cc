#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sourcemeta/hydra/httpserver.h>

TEST(HTTPServer_UUID, random) {
  const auto uuid_1{sourcemeta::hydra::http::uuid()};
  const auto uuid_2{sourcemeta::hydra::http::uuid()};
  const auto uuid_3{sourcemeta::hydra::http::uuid()};
  EXPECT_FALSE(uuid_1 == uuid_2);
  EXPECT_FALSE(uuid_1 == uuid_3);
  EXPECT_FALSE(uuid_2 == uuid_3);
}

TEST(HTTPServer_UUID, length_is_36) {
  const auto uuid{sourcemeta::hydra::http::uuid()};
  EXPECT_EQ(uuid.size(), 36);
}

// Looks like by default, GoogleTest won't recognize POSIX regular expressions
// on MSVC and its too verbose to write this regular expression to not use
// facilities like `[` and `]`
// See
// https://google.github.io/googletest/advanced.html#regular-expression-syntax
#if !defined(_MSC_VER)
TEST(HTTPServer, regex) {
  const auto uuid{sourcemeta::hydra::http::uuid()};
  const auto regex{
      "^[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$"};
  EXPECT_THAT(uuid, ::testing::MatchesRegex(regex));
}
#endif
