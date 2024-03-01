#include <gtest/gtest.h>

#include <sourcemeta/hydra/bucket.h>

#include "http_base_url.h"

TEST(Bucket_JSON, no_cache_single) {
  sourcemeta::hydra::Bucket bucket{HTTP_BASE_URL() + "/bucket", "us-east-1",
                                   "123456789", "ultra-secret"};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response{
      bucket.fetch_json("1.json")};
  EXPECT_TRUE(response.has_value());
  EXPECT_TRUE(response.value().data.is_object());
  EXPECT_EQ(response.value().data.size(), 1);
  EXPECT_TRUE(response.value().data.defines("foo"));
  EXPECT_TRUE(response.value().data.at("foo").is_integer());
  EXPECT_EQ(response.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response.value().etag, "\"1111111111\"");
  EXPECT_FALSE(response.value().cache_hit);
}

TEST(Bucket_JSON, no_cache_idempotent) {
  sourcemeta::hydra::Bucket bucket{HTTP_BASE_URL() + "/bucket", "us-east-1",
                                   "123456789", "ultra-secret"};

  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_1{
      bucket.fetch_json("1.json")};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_2{
      bucket.fetch_json("1.json")};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_3{
      bucket.fetch_json("1.json")};

  EXPECT_TRUE(response_1.has_value());
  EXPECT_TRUE(response_1.value().data.is_object());
  EXPECT_EQ(response_1.value().data.size(), 1);
  EXPECT_TRUE(response_1.value().data.defines("foo"));
  EXPECT_TRUE(response_1.value().data.at("foo").is_integer());
  EXPECT_EQ(response_1.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_1.value().etag, "\"1111111111\"");
  EXPECT_FALSE(response_1.value().cache_hit);

  EXPECT_TRUE(response_2.has_value());
  EXPECT_TRUE(response_2.value().data.is_object());
  EXPECT_EQ(response_2.value().data.size(), 1);
  EXPECT_TRUE(response_2.value().data.defines("foo"));
  EXPECT_TRUE(response_2.value().data.at("foo").is_integer());
  EXPECT_EQ(response_2.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_2.value().etag, "\"1111111111\"");
  EXPECT_FALSE(response_2.value().cache_hit);

  EXPECT_TRUE(response_3.has_value());
  EXPECT_TRUE(response_3.value().data.is_object());
  EXPECT_EQ(response_3.value().data.size(), 1);
  EXPECT_TRUE(response_3.value().data.defines("foo"));
  EXPECT_TRUE(response_3.value().data.at("foo").is_integer());
  EXPECT_EQ(response_3.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_3.value().etag, "\"1111111111\"");
  EXPECT_FALSE(response_3.value().cache_hit);
}

TEST(Bucket_JSON, cache_none_with_policy) {
  sourcemeta::hydra::Bucket bucket{
      HTTP_BASE_URL() + "/bucket", "us-east-1", "123456789", "ultra-secret",
      sourcemeta::hydra::BucketCachePolicy::Indefinitely};

  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_1{
      bucket.fetch_json("1.json")};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_2{
      bucket.fetch_json("1.json")};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_3{
      bucket.fetch_json("1.json")};

  EXPECT_TRUE(response_1.has_value());
  EXPECT_TRUE(response_1.value().data.is_object());
  EXPECT_EQ(response_1.value().data.size(), 1);
  EXPECT_TRUE(response_1.value().data.defines("foo"));
  EXPECT_TRUE(response_1.value().data.at("foo").is_integer());
  EXPECT_EQ(response_1.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_1.value().etag, "\"1111111111\"");
  EXPECT_FALSE(response_1.value().cache_hit);

  EXPECT_TRUE(response_2.has_value());
  EXPECT_TRUE(response_2.value().data.is_object());
  EXPECT_EQ(response_2.value().data.size(), 1);
  EXPECT_TRUE(response_2.value().data.defines("foo"));
  EXPECT_TRUE(response_2.value().data.at("foo").is_integer());
  EXPECT_EQ(response_2.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_2.value().etag, "\"1111111111\"");
  EXPECT_FALSE(response_2.value().cache_hit);

  EXPECT_TRUE(response_3.has_value());
  EXPECT_TRUE(response_3.value().data.is_object());
  EXPECT_EQ(response_3.value().data.size(), 1);
  EXPECT_TRUE(response_3.value().data.defines("foo"));
  EXPECT_TRUE(response_3.value().data.at("foo").is_integer());
  EXPECT_EQ(response_3.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_3.value().etag, "\"1111111111\"");
  EXPECT_FALSE(response_3.value().cache_hit);
}

TEST(Bucket_JSON, cache_indefinitely) {
  sourcemeta::hydra::Bucket bucket{
      HTTP_BASE_URL() + "/bucket",
      "us-east-1",
      "123456789",
      "ultra-secret",
      sourcemeta::hydra::BucketCachePolicy::Indefinitely,
      100000};

  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_1{
      bucket.fetch_json("1.json")};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_2{
      bucket.fetch_json("1.json")};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_3{
      bucket.fetch_json("1.json")};

  EXPECT_TRUE(response_1.has_value());
  EXPECT_TRUE(response_1.value().data.is_object());
  EXPECT_EQ(response_1.value().data.size(), 1);
  EXPECT_TRUE(response_1.value().data.defines("foo"));
  EXPECT_TRUE(response_1.value().data.at("foo").is_integer());
  EXPECT_EQ(response_1.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_1.value().etag, "\"1111111111\"");
  EXPECT_FALSE(response_1.value().cache_hit);

  EXPECT_TRUE(response_2.has_value());
  EXPECT_TRUE(response_2.value().data.is_object());
  EXPECT_EQ(response_2.value().data.size(), 1);
  EXPECT_TRUE(response_2.value().data.defines("foo"));
  EXPECT_TRUE(response_2.value().data.at("foo").is_integer());
  EXPECT_EQ(response_2.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_2.value().etag, "\"1111111111\"");
  EXPECT_TRUE(response_2.value().cache_hit);

  EXPECT_TRUE(response_3.has_value());
  EXPECT_TRUE(response_3.value().data.is_object());
  EXPECT_EQ(response_3.value().data.size(), 1);
  EXPECT_TRUE(response_3.value().data.defines("foo"));
  EXPECT_TRUE(response_3.value().data.at("foo").is_integer());
  EXPECT_EQ(response_3.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_3.value().etag, "\"1111111111\"");
  EXPECT_TRUE(response_3.value().cache_hit);
}

TEST(Bucket_JSON, cache_indefinitely_with_without_prefix_slash) {
  sourcemeta::hydra::Bucket bucket{
      HTTP_BASE_URL() + "/bucket",
      "us-east-1",
      "123456789",
      "ultra-secret",
      sourcemeta::hydra::BucketCachePolicy::Indefinitely,
      100000};

  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_1{
      bucket.fetch_json("1.json")};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_2{
      bucket.fetch_json("/1.json")};

  EXPECT_TRUE(response_1.has_value());
  EXPECT_TRUE(response_1.value().data.is_object());
  EXPECT_EQ(response_1.value().data.size(), 1);
  EXPECT_TRUE(response_1.value().data.defines("foo"));
  EXPECT_TRUE(response_1.value().data.at("foo").is_integer());
  EXPECT_EQ(response_1.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_1.value().etag, "\"1111111111\"");
  EXPECT_FALSE(response_1.value().cache_hit);

  EXPECT_TRUE(response_2.has_value());
  EXPECT_TRUE(response_2.value().data.is_object());
  EXPECT_EQ(response_2.value().data.size(), 1);
  EXPECT_TRUE(response_2.value().data.defines("foo"));
  EXPECT_TRUE(response_2.value().data.at("foo").is_integer());
  EXPECT_EQ(response_2.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_2.value().etag, "\"1111111111\"");
  EXPECT_TRUE(response_2.value().cache_hit);
}

TEST(Bucket_JSON, cache_etag_match) {
  sourcemeta::hydra::Bucket bucket{HTTP_BASE_URL() + "/bucket",
                                   "us-east-1",
                                   "123456789",
                                   "ultra-secret",
                                   sourcemeta::hydra::BucketCachePolicy::ETag,
                                   100000};

  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_1{
      bucket.fetch_json("1.json")};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_2{
      bucket.fetch_json("1.json")};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_3{
      bucket.fetch_json("1.json")};

  EXPECT_TRUE(response_1.has_value());
  EXPECT_TRUE(response_1.value().data.is_object());
  EXPECT_EQ(response_1.value().data.size(), 1);
  EXPECT_TRUE(response_1.value().data.defines("foo"));
  EXPECT_TRUE(response_1.value().data.at("foo").is_integer());
  EXPECT_EQ(response_1.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_1.value().etag, "\"1111111111\"");
  EXPECT_FALSE(response_1.value().cache_hit);

  EXPECT_TRUE(response_2.has_value());
  EXPECT_TRUE(response_2.value().data.is_object());
  EXPECT_EQ(response_2.value().data.size(), 1);
  EXPECT_TRUE(response_2.value().data.defines("foo"));
  EXPECT_TRUE(response_2.value().data.at("foo").is_integer());
  EXPECT_EQ(response_2.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_2.value().etag, "\"1111111111\"");
  EXPECT_TRUE(response_2.value().cache_hit);

  EXPECT_TRUE(response_3.has_value());
  EXPECT_TRUE(response_3.value().data.is_object());
  EXPECT_EQ(response_3.value().data.size(), 1);
  EXPECT_TRUE(response_3.value().data.defines("foo"));
  EXPECT_TRUE(response_3.value().data.at("foo").is_integer());
  EXPECT_EQ(response_3.value().data.at("foo").to_integer(), 1);
  EXPECT_EQ(response_3.value().etag, "\"1111111111\"");
  EXPECT_TRUE(response_3.value().cache_hit);
}

TEST(Bucket_JSON, cache_etag_mismatch) {
  sourcemeta::hydra::Bucket bucket{HTTP_BASE_URL() + "/bucket",
                                   "us-east-1",
                                   "123456789",
                                   "ultra-secret",
                                   sourcemeta::hydra::BucketCachePolicy::ETag,
                                   100000};

  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_1{
      bucket.fetch_json("incremental.json")};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_2{
      bucket.fetch_json("incremental.json")};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_3{
      bucket.fetch_json("incremental.json")};

  EXPECT_TRUE(response_1.has_value());
  EXPECT_TRUE(response_1.value().data.is_object());
  EXPECT_EQ(response_1.value().data.size(), 1);
  EXPECT_TRUE(response_1.value().data.defines("value"));
  EXPECT_TRUE(response_1.value().data.at("value").is_integer());
  EXPECT_FALSE(response_1.value().cache_hit);

  EXPECT_TRUE(response_2.has_value());
  EXPECT_TRUE(response_2.value().data.is_object());
  EXPECT_EQ(response_2.value().data.size(), 1);
  EXPECT_TRUE(response_2.value().data.defines("value"));
  EXPECT_TRUE(response_2.value().data.at("value").is_integer());
  EXPECT_TRUE(response_2.value().data.at("value").to_integer() >
              response_1.value().data.at("value").to_integer());
  EXPECT_NE(response_2.value().etag, response_1.value().etag);
  EXPECT_FALSE(response_2.value().cache_hit);

  EXPECT_TRUE(response_3.has_value());
  EXPECT_TRUE(response_3.value().data.is_object());
  EXPECT_EQ(response_3.value().data.size(), 1);
  EXPECT_TRUE(response_3.value().data.defines("value"));
  EXPECT_TRUE(response_3.value().data.at("value").is_integer());
  EXPECT_TRUE(response_3.value().data.at("value").to_integer() >
              response_2.value().data.at("value").to_integer());
  EXPECT_NE(response_3.value().etag, response_1.value().etag);
  EXPECT_NE(response_3.value().etag, response_2.value().etag);
  EXPECT_FALSE(response_3.value().cache_hit);
}
