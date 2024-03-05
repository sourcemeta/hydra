#include <gtest/gtest.h>

#include <sourcemeta/hydra/bucket_aws_sigv4.h>

#include <ctime>
#include <iomanip>
#include <ios>

TEST(Bucket_aws_sigv4, scope_20151021_us_east_1) {
  std::ostringstream result;
  sourcemeta::hydra::aws_sigv4_scope("20151021", "us-east-1", result);
  EXPECT_EQ(result.str(), "20151021/us-east-1/s3/aws4_request");
}

TEST(Bucket_aws_sigv4, key_my_secret_key_us_east_1_20151021) {
  const auto result{sourcemeta::hydra::aws_sigv4_key("my-secret-key",
                                                     "us-east-1", "20151021")};
  std::ostringstream hex;
  hex << std::hex << std::setfill('0');
  for (const auto character : result) {
    hex << std::setw(2)
        << static_cast<unsigned int>(static_cast<unsigned char>(character));
  }

  EXPECT_EQ(hex.str(),
            "39cfa919fbbce8828d495506d3305679a00d5c5672d6629deb32519df2665b75");
}

TEST(Bucket_aws_sigv4, canonical_example_1) {
  const auto result{sourcemeta::hydra::aws_sigv4_canonical(
      sourcemeta::hydra::http::Method::GET, "localhost:9000",
      "/schemas/data/foo/bar/v1.json",
      "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
      "20230915T164344Z")};
  EXPECT_EQ(
      result,
      "GET\n/schemas/data/foo/bar/"
      "v1.json\n\nhost:localhost:9000\nx-amz-content-sha256:"
      "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\nx-amz-"
      "date:20230915T164344Z\n\nhost;x-amz-content-sha256;x-amz-"
      "date\ne3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
}

TEST(Bucket_aws_sigv4, complete_example_1) {
  std::istringstream stream{"Fri, 15 Sep 2023 19:07:50 GMT"};
  std::tm parts = {};
  stream >> std::get_time(&parts, "%a, %d %b %Y %H:%M:%S GMT");
  EXPECT_FALSE(stream.fail());

#if defined(_MSC_VER)
  const auto date{std::chrono::system_clock::from_time_t(_mkgmtime(&parts))};
#else
  const auto date{std::chrono::system_clock::from_time_t(timegm(&parts))};
#endif

  const auto headers{sourcemeta::hydra::aws_sigv4(
      sourcemeta::hydra::http::Method::GET,
      sourcemeta::jsontoolkit::URI{
          "http://localhost:9000/schemas/data/foo/bar/v1.json"},
      "intelligence-api", "12345678", "us-east-1", date)};

  EXPECT_EQ(headers.size(), 4);
  EXPECT_TRUE(headers.contains("host"));
  EXPECT_TRUE(headers.contains("x-amz-content-sha256"));
  EXPECT_TRUE(headers.contains("x-amz-date"));
  EXPECT_TRUE(headers.contains("authorization"));

  EXPECT_EQ(headers.at("host"), "localhost:9000");
  EXPECT_EQ(headers.at("x-amz-content-sha256"),
            "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
  EXPECT_EQ(headers.at("x-amz-date"), "20230915T190750Z");
  EXPECT_EQ(headers.at("authorization"),
            "AWS4-HMAC-SHA256 "
            "Credential=intelligence-api/20230915/us-east-1/s3/aws4_request, "
            "SignedHeaders=host;x-amz-content-sha256;x-amz-date, "
            "Signature="
            "52d0a66296564b851a772a44a507f43f19c4120a8b2cabe003724fc7df8c81f2");
}
