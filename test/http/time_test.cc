#include <gtest/gtest.h>

#include <chrono>
#include <ctime>
#include <stdexcept>

#include <sourcemeta/hydra/http.h>

TEST(HTTP_Time, time_to_gmt) {
  std::tm parts = {};
  parts.tm_year = 115;
  parts.tm_mon = 9;
  parts.tm_mday = 21;
  parts.tm_hour = 11;
  parts.tm_min = 28;
  parts.tm_sec = 0;
  parts.tm_isdst = 0;

#if defined(_MSC_VER)
  const auto point{std::chrono::system_clock::from_time_t(_mkgmtime(&parts))};
#else
  const auto point{std::chrono::system_clock::from_time_t(timegm(&parts))};
#endif

  EXPECT_EQ(sourcemeta::hydra::http::to_gmt(point),
            "Wed, 21 Oct 2015 11:28:00 GMT");
}

TEST(HTTP_Time, gmt_to_time) {
  const auto point{
      sourcemeta::hydra::http::from_gmt("Wed, 21 Oct 2015 11:28:00 GMT")};

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

TEST(HTTP_Time, gmt_e2e) {
  const auto point{
      sourcemeta::hydra::http::from_gmt("Wed, 21 Oct 2015 11:28:00 GMT")};
  const auto timestamp{sourcemeta::hydra::http::to_gmt(point)};
  EXPECT_EQ(timestamp, "Wed, 21 Oct 2015 11:28:00 GMT");
}

TEST(HTTP_Time, gmt_invalid) {
  EXPECT_THROW(sourcemeta::hydra::http::from_gmt("FOO"), std::invalid_argument);
}

TEST(HTTP_Time, gmt_comparison_equal) {
  EXPECT_EQ(sourcemeta::hydra::http::from_gmt("Wed, 21 Oct 2015 11:28:00 GMT"),
            sourcemeta::hydra::http::from_gmt("Wed, 21 Oct 2015 11:28:00 GMT"));
}

TEST(HTTP_Time, gmt_comparison_less_than) {
  EXPECT_TRUE(
      sourcemeta::hydra::http::from_gmt("Wed, 21 Oct 2015 11:27:00 GMT") <
      sourcemeta::hydra::http::from_gmt("Wed, 21 Oct 2015 11:28:00 GMT"));
}

TEST(HTTP_Time, gmt_comparison_greater_than) {
  EXPECT_TRUE(
      sourcemeta::hydra::http::from_gmt("Wed, 21 Oct 2100 11:28:00 GMT") >
      sourcemeta::hydra::http::from_gmt("Wed, 21 Oct 2015 11:28:00 GMT"));
}
