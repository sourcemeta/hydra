#include <gtest/gtest.h>

#include <sourcemeta/hydra/bucket_aws_sigv4.h>

#include <sstream>

TEST(Bucket_aws_sigv4, sha256_canonical_request) {
  std::ostringstream result;
  sourcemeta::hydra::aws_sigv4_sha256("GET /schemas/data/foo/bar/v1.json",
                                      result);
  EXPECT_EQ(result.str(),
            "120bfe5a59d74af4450206e0c0f7c3583480abb6ad71fb9901371bb0c589ec1b");
}

TEST(Bucket_aws_sigv4, sha256_empty_string) {
  std::ostringstream result;
  sourcemeta::hydra::aws_sigv4_sha256("", result);
  EXPECT_EQ(result.str(),
            "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
}
