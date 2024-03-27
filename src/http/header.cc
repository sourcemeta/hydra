#include <sourcemeta/hydra/http_header.h>
#include <sourcemeta/hydra/http_time.h>

namespace sourcemeta::hydra::http {

auto header_gmt(const std::string &value)
    -> std::chrono::system_clock::time_point {
  return from_gmt(value);
}

} // namespace sourcemeta::hydra::http
