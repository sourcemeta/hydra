#ifndef SOURCEMETA_HYDRA_HTTPSERVER_REQUEST_H
#define SOURCEMETA_HYDRA_HTTPSERVER_REQUEST_H

#if defined(__Unikraft__)
#define SOURCEMETA_HYDRA_HTTPSERVER_EXPORT
#else
#include "httpserver_export.h"
#endif

#include <sourcemeta/hydra/http.h>

#include <cstdint>     // std::uint8_t
#include <memory>      // std::unique_ptr
#include <optional>    // std::optional
#include <string>      // std::string
#include <string_view> // std::string_view

namespace sourcemeta::hydra::http {

/// @ingroup httpserver
/// This class encapsulates the incoming HTTP request
class SOURCEMETA_HYDRA_HTTPSERVER_EXPORT ServerRequest {
public:
// These constructors are considered private. Do not use them directly.
#if !defined(DOXYGEN)
  ServerRequest(void *const handler);
  ~ServerRequest();
#endif

  /// Get the HTTP method of the incoming request. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/httpserver.h>
  /// #include <sstream>
  ///
  /// sourcemeta::hydra::http::Server server;
  ///
  /// static auto
  /// on_root(const sourcemeta::hydra::http::ServerRequest &request,
  ///         sourcemeta::hydra::http::ServerResponse &response) -> void {
  ///   response.status(sourcemeta::hydra::http::Status::OK);
  ///   std::ostringstream result;
  ///   result << "Got method: " << request.method();
  ///   response.end(result.str());
  /// }
  ///
  /// server.route(sourcemeta::hydra::http::Method::GET, "/", on_root);
  /// ```
  auto method() const -> Method;

  /// Get the value of a header of the incoming request. The header name is
  /// expected to be lowercase. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/httpserver.h>
  /// #include <sstream>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Server server;
  ///
  /// static auto
  /// on_root(const sourcemeta::hydra::http::ServerRequest &request,
  ///         sourcemeta::hydra::http::ServerResponse &response) -> void {
  ///   response.status(sourcemeta::hydra::http::Status::OK);
  ///   const auto host{request.header("host")};
  ///   assert(host.has_value());
  ///   std::ostringstream result;
  ///   result << "The host is: " << host.value();
  ///   response.end(result.str());
  /// }
  ///
  /// server.route(sourcemeta::hydra::http::Method::GET, "/", on_root);
  /// ```
  auto header(std::string_view key) const -> std::optional<std::string>;

  /// Get the value of a query string in the incoming request URL. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/httpserver.h>
  /// #include <sstream>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Server server;
  ///
  /// static auto
  /// on_root(const sourcemeta::hydra::http::ServerRequest &request,
  ///         sourcemeta::hydra::http::ServerResponse &response) -> void {
  ///   response.status(sourcemeta::hydra::http::Status::OK);
  ///   std::ostringstream result;
  ///   const auto foo{request.query("foo")};
  ///   if (foo.has_value()) {
  ///     result << "Foo: " << foo.value();
  ///   } else {
  ///     result << "Try passing a ?foo= query string\n";
  ///   }
  ///
  ///   response.end(result.str());
  /// }
  ///
  /// server.route(sourcemeta::hydra::http::Method::GET, "/", on_root);
  /// ```
  auto query(std::string_view key) const -> std::optional<std::string>;

  /// Get the path of the incoming request URL. Note that the path does not
  /// include query or fragments. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/httpserver.h>
  /// #include <sstream>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Server server;
  ///
  /// static auto
  /// on_root(const sourcemeta::hydra::http::ServerRequest &request,
  ///         sourcemeta::hydra::http::ServerResponse &response) -> void {
  ///   response.status(sourcemeta::hydra::http::Status::OK);
  ///   std::ostringstream result;
  ///   result << request.path();
  ///   response.end(result.str());
  /// }
  ///
  /// server.route(sourcemeta::hydra::http::Method::GET, "/", on_root);
  /// ```
  auto path() const -> std::string;

  /// Get a parameter of the request URL by position. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/httpserver.h>
  /// #include <sstream>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Server server;
  ///
  /// static auto
  /// on_root(const sourcemeta::hydra::http::ServerRequest &request,
  ///         sourcemeta::hydra::http::ServerResponse &response) -> void {
  ///   response.status(sourcemeta::hydra::http::Status::OK);
  ///   std::ostringstream result;
  ///   // Matches ":bar"
  ///   result << request.parameter(0);
  ///   response.end(result.str());
  /// }
  ///
  /// server.route(sourcemeta::hydra::http::Method::GET, "/foo/:bar", on_root);
  /// ```
  auto parameter(const std::uint8_t index) const -> std::string;

private:
  // PIMPL idiom to hide uWebSockets
  struct Internal;
  std::unique_ptr<Internal> internal;
};

} // namespace sourcemeta::hydra::http

#endif
