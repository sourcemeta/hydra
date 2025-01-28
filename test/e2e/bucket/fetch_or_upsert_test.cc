#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/hydra/bucket.h>

#include "environment.h"

TEST(e2e_Bucket_JSON, fetch_or_upsert_simple) {
  sourcemeta::hydra::Bucket bucket{BUCKET_BASE_URL(), BUCKET_REGION(),
                                   BUCKET_ACCESS_KEY(), BUCKET_SECRET_KEY()};

  std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_1{
      bucket
          .fetch_or_upsert("/data/fetch_or_upsert_simple.json",
                           []() -> sourcemeta::core::JSON {
                             return sourcemeta::core::parse(
                                 R"JSON({ "hello": "world" })JSON");
                           })
          .get()};

  EXPECT_TRUE(response_1.has_value());
  EXPECT_TRUE(response_1.value().data.is_object());
  EXPECT_EQ(response_1.value().data.size(), 1);
  EXPECT_TRUE(response_1.value().data.defines("hello"));
  EXPECT_TRUE(response_1.value().data.at("hello").is_string());
  EXPECT_EQ(response_1.value().data.at("hello").to_string(), "world");

  std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response_2{
      bucket
          .fetch_or_upsert("/data/fetch_or_upsert_simple.json",
                           []() -> sourcemeta::core::JSON {
                             return sourcemeta::core::parse(
                                 R"JSON({ "test": "xxxxxxxxxx" })JSON");
                           })
          .get()};

  EXPECT_TRUE(response_2.has_value());
  EXPECT_TRUE(response_2.value().data.is_object());
  EXPECT_EQ(response_2.value().data.size(), 1);
  EXPECT_TRUE(response_2.value().data.defines("hello"));
  EXPECT_TRUE(response_2.value().data.at("hello").is_string());
  EXPECT_EQ(response_2.value().data.at("hello").to_string(), "world");
}
