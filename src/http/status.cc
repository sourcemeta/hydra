#include <sourcemeta/hydra/http_status.h>

#include <ostream>     // std::ostream
#include <type_traits> // std::underlying_type_t

namespace sourcemeta::hydra::http {

auto operator<<(std::ostream &stream, const Status value) -> std::ostream & {
  return stream << static_cast<std::underlying_type_t<Status>>(value);
}

} // namespace sourcemeta::hydra::http
