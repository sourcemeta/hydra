#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sourcemeta/hydra/crypto.h>

TEST(Crypto_uuid, v4_regex) {
  const auto uuid{sourcemeta::hydra::uuid()};
#if defined(_MSC_VER)
  EXPECT_THAT(uuid,
              // Windows regular expressions don't support [, ], {, and }
              testing::MatchesRegex("^........-....-....-....-............$"));
#else
  EXPECT_THAT(uuid,
              testing::MatchesRegex("^[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-"
                                    "9a-f]{4}-[0-9a-f]{12}$"));
#endif
}

TEST(Crypto_uuid, idempotent) {
  const auto uuid_1{sourcemeta::hydra::uuid()};
  const auto uuid_2{sourcemeta::hydra::uuid()};
  const auto uuid_3{sourcemeta::hydra::uuid()};
  EXPECT_NE(uuid_1, uuid_2);
  EXPECT_NE(uuid_2, uuid_3);
  EXPECT_NE(uuid_3, uuid_1);
}
