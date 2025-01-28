#include <gtest/gtest.h>

#include <random>

#include <sourcemeta/core/json.h>
#include <sourcemeta/hydra/bucket.h>

#include "environment.h"

TEST(e2e_Bucket_JSON, upsert_example_9999) {
  const sourcemeta::core::JSON document =
      sourcemeta::core::parse(R"JSON({ "foo": 9999 })JSON");

  sourcemeta::hydra::Bucket bucket{BUCKET_BASE_URL(), BUCKET_REGION(),
                                   BUCKET_ACCESS_KEY(), BUCKET_SECRET_KEY()};

  bucket.upsert_json("/data/upsert_example_9999.json", document).wait();

  const std::optional<sourcemeta::hydra::Bucket::ResponseJSON> response{
      bucket.fetch_json("/data/upsert_example_9999.json").get()};

  EXPECT_TRUE(response.has_value());
  EXPECT_TRUE(response.value().data.is_object());
  EXPECT_EQ(response.value().data.size(), 1);
  EXPECT_TRUE(response.value().data.defines("foo"));
  EXPECT_TRUE(response.value().data.at("foo").is_integer());
  EXPECT_EQ(response.value().data.at("foo").to_integer(), 9999);

  // We don't cache uploads by default
  EXPECT_FALSE(response.value().cache_hit);
}
