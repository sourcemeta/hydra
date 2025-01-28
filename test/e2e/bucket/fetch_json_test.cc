#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/hydra/bucket.h>

#include "environment.h"

TEST(e2e_Bucket_JSON, missing) {
  sourcemeta::hydra::Bucket bucket{BUCKET_BASE_URL(), BUCKET_REGION(),
                                   BUCKET_ACCESS_KEY(), BUCKET_SECRET_KEY()};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response{
      bucket.fetch_json("/data/non-existent.json").get()};
  EXPECT_FALSE(response.has_value());
}

TEST(e2e_Bucket_JSON, no_cache_single) {
  sourcemeta::hydra::Bucket bucket{BUCKET_BASE_URL(), BUCKET_REGION(),
                                   BUCKET_ACCESS_KEY(), BUCKET_SECRET_KEY()};

  const sourcemeta::core::JSON document =
      sourcemeta::core::parse(R"JSON({ "foo": 1 })JSON");
  bucket.upsert_json("/data/no_cache_single.json", document).wait();

  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response{
      bucket.fetch_json("/data/no_cache_single.json").get()};
  EXPECT_TRUE(response.has_value());
  EXPECT_EQ(response.value().data, document);
  EXPECT_FALSE(response.value().cache_hit);
}

TEST(e2e_Bucket_JSON, no_cache_idempotent) {
  sourcemeta::hydra::Bucket bucket{BUCKET_BASE_URL(), BUCKET_REGION(),
                                   BUCKET_ACCESS_KEY(), BUCKET_SECRET_KEY()};

  const sourcemeta::core::JSON document =
      sourcemeta::core::parse(R"JSON({ "foo": 1 })JSON");
  bucket.upsert_json("/data/no_cache_idempotent.json", document).wait();

  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_1{
      bucket.fetch_json("/data/no_cache_idempotent.json").get()};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_2{
      bucket.fetch_json("/data/no_cache_idempotent.json").get()};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_3{
      bucket.fetch_json("/data/no_cache_idempotent.json").get()};

  EXPECT_TRUE(response_1.has_value());
  EXPECT_EQ(response_1.value().data, document);
  EXPECT_FALSE(response_1.value().cache_hit);

  EXPECT_TRUE(response_2.has_value());
  EXPECT_EQ(response_2.value().data, response_1.value().data);
  EXPECT_EQ(response_2.value().etag, response_1.value().etag);
  EXPECT_FALSE(response_2.value().cache_hit);

  EXPECT_TRUE(response_3.has_value());
  EXPECT_EQ(response_3.value().data, response_1.value().data);
  EXPECT_EQ(response_3.value().data, response_2.value().data);
  EXPECT_EQ(response_3.value().etag, response_1.value().etag);
  EXPECT_EQ(response_3.value().etag, response_2.value().etag);
  EXPECT_FALSE(response_3.value().cache_hit);
}

TEST(e2e_Bucket_JSON, cache_none_with_policy) {
  sourcemeta::hydra::Bucket bucket{
      BUCKET_BASE_URL(), BUCKET_REGION(), BUCKET_ACCESS_KEY(),
      BUCKET_SECRET_KEY(), sourcemeta::hydra::BucketCachePolicy::Indefinitely};

  const sourcemeta::core::JSON document =
      sourcemeta::core::parse(R"JSON({ "foo": 1 })JSON");
  bucket.upsert_json("/data/cache_none_with_policy.json", document).wait();

  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_1{
      bucket.fetch_json("/data/cache_none_with_policy.json").get()};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_2{
      bucket.fetch_json("/data/cache_none_with_policy.json").get()};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_3{
      bucket.fetch_json("/data/cache_none_with_policy.json").get()};

  EXPECT_TRUE(response_1.has_value());
  EXPECT_EQ(response_1.value().data, document);
  EXPECT_FALSE(response_1.value().cache_hit);

  EXPECT_TRUE(response_2.has_value());
  EXPECT_EQ(response_2.value().data, response_1.value().data);
  EXPECT_EQ(response_2.value().etag, response_1.value().etag);
  EXPECT_FALSE(response_2.value().cache_hit);

  EXPECT_TRUE(response_3.has_value());
  EXPECT_EQ(response_3.value().data, response_1.value().data);
  EXPECT_EQ(response_3.value().data, response_2.value().data);
  EXPECT_EQ(response_3.value().etag, response_1.value().etag);
  EXPECT_EQ(response_3.value().etag, response_2.value().etag);
  EXPECT_FALSE(response_3.value().cache_hit);
}

TEST(e2e_Bucket_JSON, cache_indefinitely) {
  sourcemeta::hydra::Bucket bucket{
      BUCKET_BASE_URL(),
      BUCKET_REGION(),
      BUCKET_ACCESS_KEY(),
      BUCKET_SECRET_KEY(),
      sourcemeta::hydra::BucketCachePolicy::Indefinitely,
      100000};

  const sourcemeta::core::JSON document =
      sourcemeta::core::parse(R"JSON({ "foo": 1 })JSON");
  bucket.upsert_json("/data/cache_indefinitely.json", document).wait();

  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_1{
      bucket.fetch_json("/data/cache_indefinitely.json").get()};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_2{
      bucket.fetch_json("/data/cache_indefinitely.json").get()};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_3{
      bucket.fetch_json("/data/cache_indefinitely.json").get()};

  EXPECT_TRUE(response_1.has_value());
  EXPECT_EQ(response_1.value().data, document);
  EXPECT_FALSE(response_1.value().cache_hit);

  EXPECT_TRUE(response_2.has_value());
  EXPECT_EQ(response_2.value().data, response_1.value().data);
  EXPECT_EQ(response_2.value().etag, response_1.value().etag);
  EXPECT_TRUE(response_2.value().cache_hit);

  EXPECT_TRUE(response_3.has_value());
  EXPECT_EQ(response_3.value().data, response_1.value().data);
  EXPECT_EQ(response_3.value().data, response_2.value().data);
  EXPECT_EQ(response_3.value().etag, response_1.value().etag);
  EXPECT_EQ(response_3.value().etag, response_2.value().etag);
  EXPECT_TRUE(response_3.value().cache_hit);
}

TEST(e2e_Bucket_JSON, cache_etag_match) {
  sourcemeta::hydra::Bucket bucket{BUCKET_BASE_URL(),
                                   BUCKET_REGION(),
                                   BUCKET_ACCESS_KEY(),
                                   BUCKET_SECRET_KEY(),
                                   sourcemeta::hydra::BucketCachePolicy::ETag,
                                   100000};

  const sourcemeta::core::JSON document =
      sourcemeta::core::parse(R"JSON({ "foo": 1 })JSON");
  bucket.upsert_json("/data/cache_etag_match.json", document).wait();

  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_1{
      bucket.fetch_json("/data/cache_etag_match.json").get()};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_2{
      bucket.fetch_json("/data/cache_etag_match.json").get()};
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_3{
      bucket.fetch_json("/data/cache_etag_match.json").get()};

  EXPECT_TRUE(response_1.has_value());
  EXPECT_EQ(response_1.value().data, document);
  EXPECT_FALSE(response_1.value().cache_hit);

  EXPECT_TRUE(response_2.has_value());
  EXPECT_EQ(response_2.value().data, response_1.value().data);
  EXPECT_EQ(response_2.value().etag, response_1.value().etag);
  EXPECT_TRUE(response_2.value().cache_hit);

  EXPECT_TRUE(response_3.has_value());
  EXPECT_EQ(response_3.value().data, response_1.value().data);
  EXPECT_EQ(response_3.value().data, response_2.value().data);
  EXPECT_EQ(response_3.value().etag, response_1.value().etag);
  EXPECT_EQ(response_3.value().etag, response_2.value().etag);
  EXPECT_TRUE(response_3.value().cache_hit);
}

TEST(e2e_Bucket_JSON, cache_etag_mismatch) {
  sourcemeta::hydra::Bucket bucket{BUCKET_BASE_URL(),
                                   BUCKET_REGION(),
                                   BUCKET_ACCESS_KEY(),
                                   BUCKET_SECRET_KEY(),
                                   sourcemeta::hydra::BucketCachePolicy::ETag,
                                   100000};

  const sourcemeta::core::JSON document_1 =
      sourcemeta::core::parse("{ \"value\": 1 }");
  bucket.upsert_json("/data/cache_etag_mismatch.json", document_1).wait();
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_1{
      bucket.fetch_json("/data/cache_etag_mismatch.json").get()};
  EXPECT_TRUE(response_1.has_value());
  EXPECT_TRUE(response_1.value().data.is_object());
  EXPECT_EQ(response_1.value().data.size(), 1);
  EXPECT_TRUE(response_1.value().data.defines("value"));
  EXPECT_TRUE(response_1.value().data.at("value").is_integer());
  EXPECT_FALSE(response_1.value().cache_hit);

  const sourcemeta::core::JSON document_2 =
      sourcemeta::core::parse("{ \"value\": 2 }");
  bucket.upsert_json("/data/cache_etag_mismatch.json", document_2).wait();
  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_2{
      bucket.fetch_json("/data/cache_etag_mismatch.json").get()};
  EXPECT_TRUE(response_1.has_value());
  EXPECT_TRUE(response_1.value().data.is_object());
  EXPECT_EQ(response_1.value().data.size(), 1);
  EXPECT_TRUE(response_1.value().data.defines("value"));
  EXPECT_TRUE(response_1.value().data.at("value").is_integer());
  EXPECT_FALSE(response_1.value().cache_hit);
}
