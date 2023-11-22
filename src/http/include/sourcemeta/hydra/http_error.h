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

// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251 4275)
#endif

/// @ingroup http
/// This class represents a general HTTP error.
class SOURCEMETA_HYDRA_HTTP_EXPORT Error : public std::exception {
public:
  // We don't want to document this internal constructor
#if !defined(DOXYGEN)
  Error(std::string message) : message_{std::move(message)} {}
#endif

  /// Get the error message
  [[nodiscard]] auto what() const noexcept -> const char * override {
    return this->message_.c_str();
  }

private:
  std::string message_;
};

#if defined(_MSC_VER)
#pragma warning(default : 4251 4275)
#endif

} // namespace sourcemeta::hydra::http

#endif
