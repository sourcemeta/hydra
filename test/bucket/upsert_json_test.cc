#include <gtest/gtest.h>

#include <sourcemeta/hydra/bucket.h>
#include <sourcemeta/jsontoolkit/json.h>

#include "http_base_url.h"

TEST(Bucket_JSON, upsert_example_1) {
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(R"JSON({ "foo": 9999 })JSON");
  sourcemeta::hydra::Bucket bucket{HTTP_BASE_URL(), "us-east-1", "123456789",
                                   "ultra-secret"};
  bucket.upsert_json("/upload.json", document).wait();
  SUCCEED();
}
