#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sourcemeta/hydra/httpserver.h>

TEST(HTTPServer_logger, default_random_id) {
  const sourcemeta::hydra::http::ServerLogger logger_1;
  const sourcemeta::hydra::http::ServerLogger logger_2;
  const sourcemeta::hydra::http::ServerLogger logger_3;

  EXPECT_FALSE(logger_1.id() == logger_2.id());
  EXPECT_FALSE(logger_1.id() == logger_3.id());
  EXPECT_FALSE(logger_2.id() == logger_3.id());
}

TEST(HTTPServer_logger, custom_id) {
  const sourcemeta::hydra::http::ServerLogger logger{"system"};
  EXPECT_EQ(logger.id(), "system");
}

TEST(HTTPServer_logger, default_id_length_is_36) {
  const sourcemeta::hydra::http::ServerLogger logger;
  EXPECT_EQ(logger.id().size(), 36);
}

// Looks like by default, GoogleTest won't recognize POSIX regular expressions
// on MSVC and its too verbose to write this regular expression to not use
// facilities like `[` and `]`
// See
// https://google.github.io/googletest/advanced.html#regular-expression-syntax
#if !defined(_MSC_VER)
TEST(HTTPServer_logger, default_id_regex) {
  const sourcemeta::hydra::http::ServerLogger logger;
  const auto regex{
      "^[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$"};
  EXPECT_THAT(logger.id(), ::testing::MatchesRegex(regex));
}
#endif
