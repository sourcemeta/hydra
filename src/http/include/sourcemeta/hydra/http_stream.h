#ifndef SOURCEMETA_HYDRA_HTTP_STREAM_H
#define SOURCEMETA_HYDRA_HTTP_STREAM_H

#if defined(__EMSCRIPTEN__) || defined(__Unikraft__)
#define SOURCEMETA_HYDRA_HTTP_EXPORT
#else
#include "http_export.h"
#endif

#include <sourcemeta/hydra/http_method.h>
#include <sourcemeta/hydra/http_status.h>

#include <cstdint>     // std::uint8_t
#include <functional>  // std::function
#include <future>      // std::future
#include <memory>      // std::unique_ptr
#include <span>        // std::span
#include <string>      // std::string
#include <string_view> // std::string_view

namespace sourcemeta::hydra::http {

class SOURCEMETA_HYDRA_HTTP_EXPORT Stream {
public:
  Stream(std::string url);
  Stream(Stream &&other) noexcept;
  auto operator=(Stream &&other) noexcept -> Stream &;

  // While possible, copy semantics are not very useful here
  Stream(const Stream &other) = delete;
  auto operator=(const Stream &other) -> Stream & = delete;

  ~Stream();

  auto method(const Method method) noexcept -> void;
  auto header(std::string_view key, std::string_view value) -> void;
  auto send() -> std::future<Status>;

  using DataCallback =
      std::function<void(const Status, std::span<const std::uint8_t>)>;
  using HeaderCallback =
      std::function<void(const Status, std::string_view, std::string_view)>;

  auto on_data(DataCallback callback) noexcept -> void;
  auto on_header(HeaderCallback callback) noexcept -> void;

private:
  struct Internal;

  // No need to make this private, as the contents of `Internal`
  // are already hidden with the PIMPL idiom.
public:
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif
  std::unique_ptr<Internal> internal;
#if defined(_MSC_VER)
#pragma warning(default : 4251)
#endif
};

} // namespace sourcemeta::hydra::http

#endif
