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
