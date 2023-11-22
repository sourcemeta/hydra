#ifndef SOURCEMETA_HYDRA_HTTP_REQUEST_H
#define SOURCEMETA_HYDRA_HTTP_REQUEST_H

#if defined(__EMSCRIPTEN__) || defined(__Unikraft__)
#define SOURCEMETA_HYDRA_HTTP_EXPORT
#else
#include "http_export.h"
#endif

#include <sourcemeta/hydra/http_method.h>
#include <sourcemeta/hydra/http_response.h>
#include <sourcemeta/hydra/http_stream.h>

#include <future>           // std::future
#include <initializer_list> // std::initializer_list
#include <set>              // std::set
#include <string>           // std::string
#include <string_view>      // std::string_view

namespace sourcemeta::hydra::http {

class SOURCEMETA_HYDRA_HTTP_EXPORT Request {
public:
  Request(std::string url);
  auto method(const Method method) noexcept -> void;
  auto capture(std::string header) -> void;
  auto capture(std::initializer_list<std::string> headers) -> void;
  auto header(std::string_view key, std::string_view value) -> void;
  auto header(std::string_view key, int value) -> void;

  auto send() -> std::future<Response>;

private:
  Stream stream;
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif
  std::set<std::string> capture_;
#if defined(_MSC_VER)
#pragma warning(default : 4251)
#endif
};

} // namespace sourcemeta::hydra::http

#endif
