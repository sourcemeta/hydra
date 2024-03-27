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
  EXPECT_EQ(result.at(0).first, "foo");
  EXPECT_EQ(result.at(0).second, 1.0);
}

TEST(HTTP_Header, list_many) {
  const auto result{sourcemeta::hydra::http::header_list("foo, bar, baz")};
  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result.at(0).first, "foo");
  EXPECT_EQ(result.at(0).second, 1.0);
  EXPECT_EQ(result.at(1).first, "bar");
  EXPECT_EQ(result.at(1).second, 1.0);
  EXPECT_EQ(result.at(2).first, "baz");
  EXPECT_EQ(result.at(2).second, 1.0);
}

TEST(HTTP_Header, list_many_compact) {
  const auto result{sourcemeta::hydra::http::header_list("foo,bar,baz")};
  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result.at(0).first, "foo");
  EXPECT_EQ(result.at(0).second, 1.0);
  EXPECT_EQ(result.at(1).first, "bar");
  EXPECT_EQ(result.at(1).second, 1.0);
  EXPECT_EQ(result.at(2).first, "baz");
  EXPECT_EQ(result.at(2).second, 1.0);
}

TEST(HTTP_Header, list_many_sparse) {
  const auto result{sourcemeta::hydra::http::header_list("foo,,baz")};
  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(result.at(0).first, "foo");
  EXPECT_EQ(result.at(0).second, 1.0);
  EXPECT_EQ(result.at(1).first, "baz");
  EXPECT_EQ(result.at(1).second, 1.0);
}

TEST(HTTP_Header, list_trailing_comma) {
  const auto result{sourcemeta::hydra::http::header_list("foo, bar,")};
  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(result.at(0).first, "foo");
  EXPECT_EQ(result.at(0).second, 1.0);
  EXPECT_EQ(result.at(1).first, "bar");
  EXPECT_EQ(result.at(1).second, 1.0);
}

TEST(HTTP_Header, list_one_with_quality_value) {
  const auto result{sourcemeta::hydra::http::header_list("foo;q=0.8")};
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result.at(0).first, "foo");
  EXPECT_NEAR(result.at(0).second, 0.8, 0.01);
}

// See https://developer.mozilla.org/en-US/docs/Glossary/Quality_values
TEST(HTTP_Header, list_mdn_example_1) {
  const auto result{sourcemeta::hydra::http::header_list(
      "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8")};
  EXPECT_EQ(result.size(), 4);
  EXPECT_EQ(result.at(0).first, "text/html");
  EXPECT_NEAR(result.at(0).second, 1.0, 0.01);
  EXPECT_EQ(result.at(1).first, "application/xhtml+xml");
  EXPECT_NEAR(result.at(1).second, 1.0, 0.01);
  EXPECT_EQ(result.at(2).first, "application/xml");
  EXPECT_NEAR(result.at(2).second, 0.9, 0.01);
  EXPECT_EQ(result.at(3).first, "*/*");
  EXPECT_NEAR(result.at(3).second, 0.8, 0.01);
}

TEST(HTTP_Header, list_mdn_example_1_out_of_order) {
  const auto result{sourcemeta::hydra::http::header_list(
      "*/*;q=0.8,text/html,application/xml;q=0.9,application/xhtml+xml")};
  EXPECT_EQ(result.size(), 4);
  EXPECT_EQ(result.at(0).first, "text/html");
  EXPECT_NEAR(result.at(0).second, 1.0, 0.01);
  EXPECT_EQ(result.at(1).first, "application/xhtml+xml");
  EXPECT_NEAR(result.at(1).second, 1.0, 0.01);
  EXPECT_EQ(result.at(2).first, "application/xml");
  EXPECT_NEAR(result.at(2).second, 0.9, 0.01);
  EXPECT_EQ(result.at(3).first, "*/*");
  EXPECT_NEAR(result.at(3).second, 0.8, 0.01);
}

// See https://developer.mozilla.org/en-US/docs/Glossary/Quality_values
TEST(HTTP_Header, list_mdn_example_2) {
  const auto result{sourcemeta::hydra::http::header_list(
      "text/html;q=0.8,text/*;q=0.8,*/*;q=0.8")};
  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result.at(0).first, "text/html");
  EXPECT_NEAR(result.at(0).second, 0.8, 0.01);
  EXPECT_EQ(result.at(1).first, "text/*");
  EXPECT_NEAR(result.at(1).second, 0.8, 0.01);
  EXPECT_EQ(result.at(2).first, "*/*");
  EXPECT_NEAR(result.at(2).second, 0.8, 0.01);
}

TEST(HTTP_Header, list_quality_0_integer) {
  const auto result{sourcemeta::hydra::http::header_list("foo;q=0")};
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result.at(0).first, "foo");
  EXPECT_NEAR(result.at(0).second, 0.0, 0.01);
}

TEST(HTTP_Header, list_quality_0_real) {
  const auto result{sourcemeta::hydra::http::header_list("foo;q=0.0")};
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result.at(0).first, "foo");
  EXPECT_NEAR(result.at(0).second, 0.0, 0.01);
}
