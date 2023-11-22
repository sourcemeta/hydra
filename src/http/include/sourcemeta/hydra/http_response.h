#ifndef SOURCEMETA_HYDRA_HTTP_RESPONSE_H
#define SOURCEMETA_HYDRA_HTTP_RESPONSE_H

#if defined(__Unikraft__)
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
  Response(const Status status, std::map<std::string, std::string> &&headers,
           std::ostringstream &&stream);

  auto status() const noexcept -> Status;
  auto header(const std::string &key) const -> std::optional<std::string>;
  auto empty() noexcept -> bool;
  auto body() -> std::istringstream &;

private:
  Status status_;
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif
  std::map<std::string, std::string> headers_;
  std::istringstream stream_;
#if defined(_MSC_VER)
#pragma warning(default : 4251)
#endif
};

} // namespace sourcemeta::hydra::http

#endif
