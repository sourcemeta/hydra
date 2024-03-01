#include <gtest/gtest.h>

#include <sourcemeta/hydra/bucket_cache.h>

TEST(Bucket_Cache, zero_logical_size) {
  sourcemeta::hydra::BucketCache<int> cache;

  cache.upsert("foo", 1);
  cache.upsert("bar", 2);
  cache.upsert("baz", 3);

  EXPECT_FALSE(cache.at("foo").has_value());
  EXPECT_FALSE(cache.at("bar").has_value());
  EXPECT_FALSE(cache.at("baz").has_value());
}

TEST(Bucket_Cache, zero_logical_size_with_custom_value_size) {
  sourcemeta::hydra::BucketCache<int> cache;

  cache.upsert("foo", 1, 10);
  cache.upsert("bar", 2, 20);
  cache.upsert("baz", 3, 30);

  EXPECT_FALSE(cache.at("foo").has_value());
  EXPECT_FALSE(cache.at("bar").has_value());
  EXPECT_FALSE(cache.at("baz").has_value());
}

TEST(Bucket_Cache, logical_size_fits_3_with_1) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  cache.upsert("foo", 1);
  const auto &entry_1{cache.at("foo")};
  EXPECT_TRUE(entry_1.has_value());
  EXPECT_EQ(entry_1.value(), 1);
}

TEST(Bucket_Cache, logical_size_fits_3_with_2) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  cache.upsert("foo", 1);
  cache.upsert("bar", 2);
  const auto &entry_1{cache.at("foo")};
  const auto &entry_2{cache.at("bar")};
  EXPECT_TRUE(entry_1.has_value());
  EXPECT_TRUE(entry_2.has_value());
  EXPECT_EQ(entry_1.value(), 1);
  EXPECT_EQ(entry_2.value(), 2);
}

TEST(Bucket_Cache, logical_size_fits_3_with_3) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  cache.upsert("foo", 1);
  cache.upsert("bar", 2);
  cache.upsert("baz", 3);
  const auto &entry_1{cache.at("foo")};
  const auto &entry_2{cache.at("bar")};
  const auto &entry_3{cache.at("baz")};
  EXPECT_TRUE(entry_1.has_value());
  EXPECT_TRUE(entry_2.has_value());
  EXPECT_TRUE(entry_3.has_value());
  EXPECT_EQ(entry_1.value(), 1);
  EXPECT_EQ(entry_2.value(), 2);
  EXPECT_EQ(entry_3.value(), 3);
}

TEST(Bucket_Cache, logical_size_fits_3_with_1_custom_size) {
  sourcemeta::hydra::BucketCache<int> cache{7};
  cache.upsert("foo", 1, 3);
  const auto &entry_1{cache.at("foo")};
  EXPECT_TRUE(entry_1.has_value());
  EXPECT_EQ(entry_1.value(), 1);
}

TEST(Bucket_Cache, logical_size_fits_3_with_2_custom_size) {
  sourcemeta::hydra::BucketCache<int> cache{7};
  cache.upsert("foo", 1, 3);
  cache.upsert("bar", 2, 2);
  const auto &entry_1{cache.at("foo")};
  const auto &entry_2{cache.at("bar")};
  EXPECT_TRUE(entry_1.has_value());
  EXPECT_TRUE(entry_2.has_value());
  EXPECT_EQ(entry_1.value(), 1);
  EXPECT_EQ(entry_2.value(), 2);
}

TEST(Bucket_Cache, logical_size_fits_3_with_3_custom_size) {
  sourcemeta::hydra::BucketCache<int> cache{7};
  cache.upsert("foo", 1, 3);
  cache.upsert("bar", 2, 2);
  cache.upsert("baz", 3, 2);
  const auto &entry_1{cache.at("foo")};
  const auto &entry_2{cache.at("bar")};
  const auto &entry_3{cache.at("baz")};
  EXPECT_TRUE(entry_1.has_value());
  EXPECT_TRUE(entry_2.has_value());
  EXPECT_TRUE(entry_3.has_value());
  EXPECT_EQ(entry_1.value(), 1);
  EXPECT_EQ(entry_2.value(), 2);
  EXPECT_EQ(entry_3.value(), 3);
}

TEST(Bucket_Cache, overflow_by_one_removes_first) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  cache.upsert("foo", 1);
  cache.upsert("bar", 2);
  cache.upsert("baz", 3);
  cache.upsert("qux", 4);

  const auto &entry_1{cache.at("foo")};
  const auto &entry_2{cache.at("bar")};
  const auto &entry_3{cache.at("baz")};
  const auto &entry_4{cache.at("qux")};

  EXPECT_FALSE(entry_1.has_value());
  EXPECT_TRUE(entry_2.has_value());
  EXPECT_TRUE(entry_3.has_value());
  EXPECT_TRUE(entry_4.has_value());

  EXPECT_EQ(entry_2.value(), 2);
  EXPECT_EQ(entry_3.value(), 3);
  EXPECT_EQ(entry_4.value(), 4);
}

TEST(Bucket_Cache, overflow_by_one_removes_many_custom_size) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  cache.upsert("foo", 1, 1);
  cache.upsert("bar", 2, 1);
  cache.upsert("baz", 3, 1);
  cache.upsert("qux", 4, 3);

  const auto &entry_1{cache.at("foo")};
  const auto &entry_2{cache.at("bar")};
  const auto &entry_3{cache.at("baz")};
  const auto &entry_4{cache.at("qux")};

  EXPECT_FALSE(entry_1.has_value());
  EXPECT_FALSE(entry_2.has_value());
  EXPECT_FALSE(entry_3.has_value());
  EXPECT_TRUE(entry_4.has_value());

  EXPECT_EQ(entry_4.value(), 4);
}

TEST(Bucket_Cache, overflow_by_one_given_reorder) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  cache.upsert("foo", 1);
  cache.upsert("bar", 2);
  cache.upsert("baz", 3);

  const auto &entry_1{cache.at("foo")};
  const auto &entry_3{cache.at("baz")};

  cache.upsert("qux", 4);

  const auto &entry_2{cache.at("bar")};
  const auto &entry_4{cache.at("qux")};

  EXPECT_TRUE(entry_1.has_value());
  EXPECT_FALSE(entry_2.has_value());
  EXPECT_TRUE(entry_3.has_value());
  EXPECT_TRUE(entry_4.has_value());

  EXPECT_EQ(entry_1.value(), 1);
  EXPECT_EQ(entry_3.value(), 3);
  EXPECT_EQ(entry_4.value(), 4);
}

TEST(Bucket_Cache, empty_does_not_fit) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  EXPECT_THROW(cache.upsert("foo", 1, 7), sourcemeta::hydra::BucketError);
  const auto &entry{cache.at("foo")};
  EXPECT_FALSE(entry.has_value());
}

TEST(Bucket_Cache, non_empty_does_not_fit) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  cache.upsert("foo", 1);
  cache.upsert("bar", 2);
  EXPECT_THROW(cache.upsert("baz", 3, 7), sourcemeta::hydra::BucketError);
  const auto &entry_1{cache.at("foo")};
  const auto &entry_2{cache.at("bar")};
  const auto &entry_3{cache.at("baz")};
  EXPECT_TRUE(entry_1.has_value());
  EXPECT_TRUE(entry_2.has_value());
  EXPECT_FALSE(entry_3.has_value());
  EXPECT_EQ(entry_1.value(), 1);
  EXPECT_EQ(entry_2.value(), 2);
}

TEST(Bucket_Cache, upsert_with_same_value) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  cache.upsert("foo", 1);
  cache.upsert("bar", 2);
  cache.upsert("baz", 3);
  cache.upsert("baz", 3);
  cache.upsert("baz", 3);
  cache.upsert("baz", 3);
  cache.upsert("baz", 3);
  const auto &entry_1{cache.at("foo")};
  const auto &entry_2{cache.at("bar")};
  const auto &entry_3{cache.at("baz")};
  EXPECT_TRUE(entry_1.has_value());
  EXPECT_TRUE(entry_2.has_value());
  EXPECT_TRUE(entry_3.has_value());
  EXPECT_EQ(entry_1.value(), 1);
  EXPECT_EQ(entry_2.value(), 2);
  EXPECT_EQ(entry_3.value(), 3);
}

TEST(Bucket_Cache, upsert_with_different_value) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  cache.upsert("foo", 1);
  cache.upsert("bar", 2);
  cache.upsert("baz", 3);
  cache.upsert("baz", 4);
  cache.upsert("baz", 5);
  cache.upsert("baz", 6);
  cache.upsert("baz", 7);
  const auto &entry_1{cache.at("foo")};
  const auto &entry_2{cache.at("bar")};
  const auto &entry_3{cache.at("baz")};
  EXPECT_TRUE(entry_1.has_value());
  EXPECT_TRUE(entry_2.has_value());
  EXPECT_TRUE(entry_3.has_value());
  EXPECT_EQ(entry_1.value(), 1);
  EXPECT_EQ(entry_2.value(), 2);
  EXPECT_EQ(entry_3.value(), 7);
}

TEST(Bucket_Cache, upsert_new_exceeds_limit) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  cache.upsert("foo", 1);
  EXPECT_THROW(cache.upsert("foo", 1, 10), sourcemeta::hydra::BucketError);
  const auto &entry{cache.at("foo")};
  EXPECT_TRUE(entry.has_value());
  EXPECT_EQ(entry.value(), 1);
}

TEST(Bucket_Cache, missing_key) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  cache.upsert("foo", 1);
  const auto &entry_1{cache.at("foo")};
  const auto &entry_2{cache.at("bar")};
  EXPECT_TRUE(entry_1.has_value());
  EXPECT_FALSE(entry_2.has_value());
  EXPECT_EQ(entry_1.value(), 1);
}

TEST(Bucket_Cache, arbitrary_access) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  cache.upsert("foo", 1);
  cache.upsert("bar", 2);
  cache.upsert("baz", 3);

  // Bar
  EXPECT_TRUE(cache.at("bar").has_value());
  EXPECT_EQ(cache.at("bar").value(), 2);

  // Foo
  EXPECT_TRUE(cache.at("foo").has_value());
  EXPECT_EQ(cache.at("foo").value(), 1);

  // Baz
  EXPECT_TRUE(cache.at("baz").has_value());
  EXPECT_EQ(cache.at("baz").value(), 3);

  // Bar
  EXPECT_TRUE(cache.at("bar").has_value());
  EXPECT_EQ(cache.at("bar").value(), 2);

  // Baz
  EXPECT_TRUE(cache.at("baz").has_value());
  EXPECT_EQ(cache.at("baz").value(), 3);

  // Foo
  EXPECT_TRUE(cache.at("foo").has_value());
  EXPECT_EQ(cache.at("foo").value(), 1);
}

TEST(Bucket_Cache, idempotency) {
  sourcemeta::hydra::BucketCache<int> cache{3};
  cache.upsert("foo", 1);
  cache.upsert("bar", 2);
  cache.upsert("baz", 3);

  EXPECT_TRUE(cache.at("foo").has_value());
  EXPECT_EQ(cache.at("foo").value(), 1);
  EXPECT_TRUE(cache.at("foo").has_value());
  EXPECT_EQ(cache.at("foo").value(), 1);
  EXPECT_TRUE(cache.at("foo").has_value());
  EXPECT_EQ(cache.at("foo").value(), 1);
  EXPECT_TRUE(cache.at("foo").has_value());
  EXPECT_EQ(cache.at("foo").value(), 1);
}
