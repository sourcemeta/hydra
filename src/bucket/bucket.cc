#include <sourcemeta/hydra/bucket.h>
#include <sourcemeta/hydra/bucket_aws_sigv4.h>
#include <sourcemeta/hydra/httpclient.h>

#include <sourcemeta/jsontoolkit/uri.h>

#include <cassert> // assert
#include <chrono>  // std::chrono::system_clock
#include <sstream> // std::ostringstream
#include <utility> // std::move

namespace sourcemeta::hydra {

Bucket::Bucket(std::string bucket_url, std::string bucket_region,
               std::string bucket_access_key, std::string bucket_secret_key,
               const BucketCachePolicy bucket_cache_policy,
               const std::uint64_t cache_byte_limit)
    // clang-format off
    : cache{std::move(cache_byte_limit)},
      cache_policy{std::move(bucket_cache_policy)},
      url{std::move(bucket_url)},
      region{std::move(bucket_region)},
      access_key{std::move(bucket_access_key)},
      secret_key{std::move(bucket_secret_key)} {}
// clang-format on

auto Bucket::fetch_json(const std::string &key) -> std::optional<ResponseJSON> {
  std::ostringstream normalized_key;
  if (key.front() != '/')
    normalized_key << '/';
  normalized_key << key;

  const auto cached_result{this->cache.at(normalized_key.str())};
  if (cached_result.has_value() &&
      this->cache_policy == BucketCachePolicy::Indefinitely) {
    return cached_result.value();
  }

  // TODO: Properly build, concat, and canonicalize the string using URI Kit
  std::ostringstream request_url;
  request_url << this->url;
  request_url << normalized_key.str();

  sourcemeta::hydra::http::ClientRequest request{request_url.str()};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.capture({"content-type", "etag", "last-modified"});

  if (cached_result.has_value() &&
      this->cache_policy == BucketCachePolicy::ETag) {
    request.header("If-None-Match", cached_result.value().etag);
  }

  // The empty content SHA256
  // TODO: Support sending a body
  auto content_checksum{
      "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"};

  for (auto &&[header, value] : aws_sigv4(
           request.method(),
           // TODO: Support constructing a URL given a string_view
           sourcemeta::jsontoolkit::URI{std::string{request.url()}},
           this->access_key, this->secret_key, this->region,
           std::move(content_checksum), std::chrono::system_clock::now())) {
    request.header(std::move(header), std::move(value));
  }

  sourcemeta::hydra::http::ClientResponse response{request.send().get()};

  const auto status{response.status()};
  if (status == sourcemeta::hydra::http::Status::NOT_FOUND) {
    return std::nullopt;
  } else if (status == sourcemeta::hydra::http::Status::NOT_MODIFIED &&
             cached_result.has_value() &&
             this->cache_policy == BucketCachePolicy::ETag) {
    return cached_result.value();
  } else if (status != sourcemeta::hydra::http::Status::OK) {
    throw BucketError("Failed to fetch JSON from storage");
  }

  assert(!response.empty());
  // No S3-compatible bucket lacks these
  assert(response.header("etag").has_value());
  assert(response.header("last-modified").has_value());

  ResponseJSON result = {sourcemeta::jsontoolkit::parse(response.body()),
                         response.header("etag").value(),
                         response.header_gmt("last-modified").value(), false};

  this->cache.upsert(normalized_key.str(),
                     {result.data, result.etag, result.last_modified, true},
                     result.data.estimated_byte_size());

  return std::optional<ResponseJSON>{std::move(result)};
}

} // namespace sourcemeta::hydra
