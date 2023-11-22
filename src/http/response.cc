#include <sourcemeta/hydra/http_response.h>
#include <sourcemeta/hydra/http_status.h>

#include <cassert>  // assert
#include <map>      // std::map
#include <optional> // std::optional, std::nullopt
#include <sstream>  // std::ostringstream, std::istringstream
#include <string>   // std::string
#include <utility>  // std::move

namespace sourcemeta::hydra::http {

Response::Response(const Status status,
                   std::map<std::string, std::string> &&headers,
                   std::ostringstream &&stream)
    : status_{status}, headers_{std::move(headers)},
      stream_{std::move(stream).str()} {}

auto Response::status() const noexcept -> Status { return this->status_; }

auto Response::header(const std::string &key) const
    -> std::optional<std::string> {
  if (!this->headers_.contains(key)) {
    return std::nullopt;
  }

  return this->headers_.at(key);
}

auto Response::empty() noexcept -> bool { return this->stream_.peek() == -1; }

auto Response::body() -> std::istringstream & {
  assert(!this->empty());
  return this->stream_;
}

} // namespace sourcemeta::hydra::http
