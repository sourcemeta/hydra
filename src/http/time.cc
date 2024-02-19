#include <sourcemeta/hydra/http_time.h>

#include <ctime>     // std::time_t, std::tm, std::gmtime, std::mktime, timegm
#include <iomanip>   // std::put_time, std::get_time
#include <sstream>   // std::ostringstream, std::istringstream
#include <stdexcept> // std::invalid_argument

namespace {
constexpr auto FORMAT_GMT{"%a, %d %b %Y %H:%M:%S GMT"};
}

namespace sourcemeta::hydra::http {

auto to_gmt(const std::chrono::system_clock::time_point time) -> std::string {
  std::time_t ctime = std::chrono::system_clock::to_time_t(time);
  std::tm *parts = std::gmtime(&ctime);
  std::ostringstream stream;
  stream << std::put_time(parts, FORMAT_GMT);
  return stream.str();
}

auto from_gmt(const std::string &time)
    -> std::chrono::system_clock::time_point {
  std::istringstream stream(time);
  std::tm parts = {};
  stream >> std::get_time(&parts, FORMAT_GMT);
  if (stream.fail()) {
    throw std::invalid_argument("Invalid GMT timestamp");
  }

  return std::chrono::system_clock::from_time_t(timegm(&parts));
}

} // namespace sourcemeta::hydra::http
