#ifndef SOURCEMETA_HYDRA_HTTPSERVER_RESPONSE_H
#define SOURCEMETA_HYDRA_HTTPSERVER_RESPONSE_H

#if defined(__Unikraft__)
#define SOURCEMETA_HYDRA_HTTPSERVER_EXPORT
#else
#include "httpserver_export.h"
#endif

#include <sourcemeta/hydra/http.h>

#include <chrono>      // std::chrono::system_clock::time_point
#include <map>         // std::map
#include <memory>      // std::unique_ptr
#include <string>      // std::string
#include <string_view> // std::string_view

namespace sourcemeta::hydra::http {

/// @ingroup httpserver
/// The content encodings supported by this implementation
enum class ServerContentEncoding { Identity, GZIP };

/// @ingroup httpserver
/// This class encapsulates the HTTP response the server responds with
class SOURCEMETA_HYDRA_HTTPSERVER_EXPORT ServerResponse {
public:
// These constructors are considered private. Do not use them directly.
#if !defined(DOXYGEN)
  ServerResponse(void *const handler);
  ~ServerResponse();
#endif

  /// Set the status code of the response. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/httpserver.h>
  ///
  /// sourcemeta::hydra::http::Server server;
  ///
  /// static auto
  /// on_root(const sourcemeta::hydra::http::ServerLogger &,
  ///         const sourcemeta::hydra::http::ServerRequest &,
  ///         sourcemeta::hydra::http::ServerResponse &response) -> void {
  ///   response.status(sourcemeta::hydra::http::Status::BAD_REQUEST);
  ///   response.end("Bad request!");
  /// }
  ///
  /// server.route(sourcemeta::hydra::http::Method::GET, "/", on_root);
  /// ```
  auto status(const Status code) -> void;

  /// Get the status code of the response. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/httpserver.h>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Server server;
  ///
  /// static auto
  /// on_root(const sourcemeta::hydra::http::ServerLogger &,
  ///         const sourcemeta::hydra::http::ServerRequest &,
  ///         sourcemeta::hydra::http::ServerResponse &response) -> void {
  ///   response.status(sourcemeta::hydra::http::Status::BAD_REQUEST);
  ///   assert(response.status() ==
  ///     sourcemeta::hydra::http::Status::BAD_REQUEST);
  ///   response.end("Bad request!");
  /// }
  ///
  /// server.route(sourcemeta::hydra::http::Method::GET, "/", on_root);
  /// ```
  auto status() const -> Status;

  /// Set a header in the response. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/httpserver.h>
  ///
  /// sourcemeta::hydra::http::Server server;
  ///
  /// static auto
  /// on_root(const sourcemeta::hydra::http::ServerLogger &,
  ///         const sourcemeta::hydra::http::ServerRequest &,
  ///         sourcemeta::hydra::http::ServerResponse &response) -> void {
  ///   response.status(sourcemeta::hydra::http::Status::OK);
  ///   response.header("X-Foo", "Bar");
  ///   response.end();
  /// }
  ///
  /// server.route(sourcemeta::hydra::http::Method::GET, "/", on_root);
  /// ```
  auto header(std::string_view key, std::string_view value) -> void;

  /// Set the `Last-Modified` HTTP header in the response. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/httpserver.h>
  ///
  /// sourcemeta::hydra::http::Server server;
  ///
  /// static auto
  /// on_root(const sourcemeta::hydra::http::ServerLogger &,
  ///         const sourcemeta::hydra::http::ServerRequest &,
  ///         sourcemeta::hydra::http::ServerResponse &response) -> void {
  ///   response.status(sourcemeta::hydra::http::Status::OK);
  ///   const auto timestamp{
  ///     sourcemeta::hydra::http::from_gmt("Wed, 21 Oct 2015 11:28:00 GMT")};
  ///   response.header_last_modified(timestamp);
  ///   response.end();
  /// }
  ///
  /// server.route(sourcemeta::hydra::http::Method::GET, "/", on_root);
  /// ```
  auto header_last_modified(const std::chrono::system_clock::time_point time)
      -> void;

  /// Set a specific content encoding for the response. The server will attempt
  /// to automatically perform content negotiation, so you typically only need
  /// to call this method to override the default choice if needed. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/httpserver.h>
  ///
  /// sourcemeta::hydra::http::Server server;
  ///
  /// static auto
  /// on_root(const sourcemeta::hydra::http::ServerLogger &,
  ///         const sourcemeta::hydra::http::ServerRequest &,
  ///         sourcemeta::hydra::http::ServerResponse &response) -> void {
  ///   response.status(sourcemeta::hydra::http::Status::OK);
  ///   // Force GZIP encoding, even if the client didn't express its
  ///   // intention using the Accept-Encoding HTTP header.
  ///   response.encoding(sourcemeta::hydra::http::ServerContentEncoding::GZIP);
  ///   response.end("Hello!");
  /// }
  ///
  /// server.route(sourcemeta::hydra::http::Method::GET, "/", on_root);
  /// ```
  auto encoding(const ServerContentEncoding encoding) -> void;

  /// Respond with a string. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/httpserver.h>
  ///
  /// sourcemeta::hydra::http::Server server;
  ///
  /// static auto
  /// on_root(const sourcemeta::hydra::http::ServerLogger &,
  ///         const sourcemeta::hydra::http::ServerRequest &,
  ///         sourcemeta::hydra::http::ServerResponse &response) -> void {
  ///   response.status(sourcemeta::hydra::http::Status::OK);
  ///   response.end("Hello world!");
  /// }
  ///
  /// server.route(sourcemeta::hydra::http::Method::GET, "/", on_root);
  /// ```
  auto end(const std::string_view message) -> void;

  /// Respond with an empty body. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/httpserver.h>
  ///
  /// sourcemeta::hydra::http::Server server;
  ///
  /// static auto
  /// on_root(const sourcemeta::hydra::http::ServerLogger &,
  ///         const sourcemeta::hydra::http::ServerRequest &,
  ///         sourcemeta::hydra::http::ServerResponse &response) -> void {
  ///   response.status(sourcemeta::hydra::http::Status::NO_CONTENT);
  ///   repsonse.end();
  /// }
  ///
  /// server.route(sourcemeta::hydra::http::Method::GET, "/", on_root);
  /// ```
  auto end() -> void;

private:
  Status code{Status::OK};
  std::map<std::string, std::string> headers;
  ServerContentEncoding content_encoding = ServerContentEncoding::Identity;
  // PIMPL idiom to hide uWebSockets
  struct Internal;
  std::unique_ptr<Internal> internal;
};

} // namespace sourcemeta::hydra::http

#endif
