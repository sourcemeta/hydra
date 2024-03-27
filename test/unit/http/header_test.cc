#include <gtest/gtest.h>

#include <chrono>
#include <ctime>
#include <sstream>

#include <sourcemeta/hydra/http.h>

TEST(HTTP_Header, gmt) {
  const auto point{
      sourcemeta::hydra::http::header_gmt("Wed, 21 Oct 2015 11:28:00 GMT")};

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

  EXPECT_EQ(point, expected);
}

TEST(HTTP_Header, list_one) {
  const auto result{sourcemeta::hydra::http::header_list("foo")};
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result.at(0), "foo");
}

TEST(HTTP_Header, list_many) {
  const auto result{sourcemeta::hydra::http::header_list("foo, bar, baz")};
  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result.at(0), "foo");
  EXPECT_EQ(result.at(1), "bar");
  EXPECT_EQ(result.at(2), "baz");
}

TEST(HTTP_Header, list_many_compact) {
  const auto result{sourcemeta::hydra::http::header_list("foo,bar,baz")};
  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result.at(0), "foo");
  EXPECT_EQ(result.at(1), "bar");
  EXPECT_EQ(result.at(2), "baz");
}

TEST(HTTP_Header, list_many_sparse) {
  const auto result{sourcemeta::hydra::http::header_list("foo,,baz")};
  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(result.at(0), "foo");
  EXPECT_EQ(result.at(1), "baz");
}

TEST(HTTP_Header, list_trailing_comma) {
  const auto result{sourcemeta::hydra::http::header_list("foo, bar,")};
  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(result.at(0), "foo");
  EXPECT_EQ(result.at(1), "bar");
}
