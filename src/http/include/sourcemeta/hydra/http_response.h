#ifndef SOURCEMETA_HYDRA_HTTP_RESPONSE_H
#define SOURCEMETA_HYDRA_HTTP_RESPONSE_H

#if defined(__EMSCRIPTEN__) || defined(__Unikraft__)
#define SOURCEMETA_HYDRA_HTTP_EXPORT
#else
#include "http_export.h"
#endif

#include <sourcemeta/hydra/http_status.h>

#include <map>      // std::map
#include <optional> // std::optional
#include <sstream>  // std::ostringstream, std::istringstream
#include <string>   // std::string

namespace sourcemeta::hydra::http {

class SOURCEMETA_HYDRA_HTTP_EXPORT Response {
public:
  // TODO: Make this constructor private
  Response(const Status status, std::map<std::string, std::string> &&headers,
           std::ostringstream &&stream);

  auto status() const noexcept -> Status;
  auto header(const std::string &key) const -> std::optional<std::string>;
  auto body() -> std::istringstream &;

private:
  Status status_;
  std::map<std::string, std::string> headers_;
  std::istringstream stream_;
};

} // namespace sourcemeta::hydra::http

#endif
