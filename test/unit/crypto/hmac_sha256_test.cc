#include <gtest/gtest.h>

#include <sourcemeta/hydra/crypto.h>

#include <iomanip>
#include <ios>
#include <sstream>

// See https://www.devglan.com/online-tools/hmac-sha256-online

TEST(Crypto_sha256, hmac_foo_bar_base64) {
  std::ostringstream hmac_sha256_result;
  sourcemeta::hydra::hmac_sha256("foo", "bar", hmac_sha256_result);
  std::ostringstream base64_result;
  sourcemeta::hydra::base64_encode(hmac_sha256_result.str(), base64_result);
  EXPECT_EQ(base64_result.str(),
            "+TILrwJJFp5zhQzWFW3tAQbiu2rYyrAbe7vr5tEGUxc=");
}

// Node.js equivalent:
//
// import * as crypto from 'node:crypto'
// const key = crypto.createHmac('sha256', 'FOO').update('BAR').digest();
// const result = crypto.createHmac('sha256', key).update('BAZ').digest('hex')
// console.log(result)
TEST(Crypto_sha256, hmac_into_hmac_sha256_hex) {
  std::ostringstream key_hmac_sha256_result;
  sourcemeta::hydra::hmac_sha256("FOO", "BAR", key_hmac_sha256_result);
  std::ostringstream hmac_sha256_result;
  sourcemeta::hydra::hmac_sha256(key_hmac_sha256_result.str(), "BAZ",
                                 hmac_sha256_result);

  std::ostringstream hex;
  hex << std::hex << std::setfill('0');
  for (const auto character : hmac_sha256_result.str()) {
    hex << std::setw(2)
        << static_cast<unsigned int>(static_cast<unsigned char>(character));
  }

  EXPECT_EQ(hex.str(),
            "b9b2bc345880d2c393b3031e9dfd064278ee30aff6f0b3c9795328fd40b937a9");
}
