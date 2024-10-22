#include <iostream>

#include <sourcemeta/hydra/bucket.h>
#include <sourcemeta/jsontoolkit/json.h>

constexpr auto BASE_URL = "http://127.0.0.1:9000/schemas";
constexpr auto REGION = "us-east-1";
constexpr auto ACCESS_KEY = "intelligence-api";
constexpr auto SECRET_KEY = "12345678";

int main() {
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(R"JSON({ "foo": 9999 })JSON");
  sourcemeta::hydra::Bucket bucket{BASE_URL, REGION, ACCESS_KEY, SECRET_KEY};
  bucket.upsert_json("/test2.json", document).wait();
  std::cout << "XXX SUCCESS\n";
  return 0;
}
