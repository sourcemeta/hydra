#include <gtest/gtest.h>

#include <sourcemeta/hydra/bucket_aws_sigv4.h>

#include <chrono>
#include <ctime>
#include <sstream>

TEST(Bucket_aws_sigv4, time_to_iso8601) {
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

  std::ostringstream output;
  sourcemeta::hydra::aws_sigv4_iso8601(point, output);
  EXPECT_EQ(output.str(), "20151021T112800Z");
}
