#ifndef SOURCEMETA_HYDRA_HTTP_ERROR_H
#define SOURCEMETA_HYDRA_HTTP_ERROR_H

#if defined(__EMSCRIPTEN__) || defined(__Unikraft__)
#define SOURCEMETA_HYDRA_HTTP_EXPORT
#else
#include "http_export.h"
#endif

#include <exception> // std::exception
#include <string>    // std::string
#include <utility>   // std::move

namespace sourcemeta::hydra::http {

class SOURCEMETA_HYDRA_HTTP_EXPORT Error : public std::exception {
public:
  Error(std::string message) : message_{std::move(message)} {}
  [[nodiscard]] auto what() const noexcept -> const char * override {
    return this->message_.c_str();
  }

private:
  std::string message_;
};

} // namespace sourcemeta::hydra::http

#endif
