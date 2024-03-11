#ifndef SOURCEMETA_HYDRA_HTTPSERVER_REQUEST_H
#define SOURCEMETA_HYDRA_HTTPSERVER_REQUEST_H

#if defined(__Unikraft__)
#define SOURCEMETA_HYDRA_HTTPSERVER_EXPORT
#else
#include "httpserver_export.h"
#endif

#include <sourcemeta/hydra/http.h>

#include <memory> // std::unique_ptr

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

private:
  // PIMPL idiom to hide uWebSockets
  struct Internal;
  std::unique_ptr<Internal> internal;
};

} // namespace sourcemeta::hydra::http

#endif
