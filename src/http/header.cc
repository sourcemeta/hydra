#include <sourcemeta/hydra/http_header.h>
#include <sourcemeta/hydra/http_time.h>

#include <sstream> // std::stringstream

namespace sourcemeta::hydra::http {

auto header_gmt(const std::string &value)
    -> std::chrono::system_clock::time_point {
  return from_gmt(value);
}

auto header_list(const std::string &value) -> std::vector<std::string> {
  std::stringstream stream{value};
  std::string token;
  std::vector<std::string> result;

  while (std::getline(stream, token, ',')) {
    const std::size_t start{token.find_first_not_of(" ")};
    const std::size_t end{token.find_last_not_of(" ")};
    if (start == std::string::npos || end == std::string::npos) {
      continue;
    }

    result.emplace_back(token.substr(start, end - start + 1));
  }

  return result;
}

} // namespace sourcemeta::hydra::http
