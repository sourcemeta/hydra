#include <sourcemeta/hydra/httpserver.h>

#include "uwebsockets.h"

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnewline-eof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
#include <src/LocalCluster.h>
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#include <cassert>  // assert
#include <cstdlib>  // EXIT_FAILURE
#include <iostream> // std::cerr
#include <ostream>  // std::ostream
#include <sstream>  // std::ostringstream
#include <utility>  // std::move

static auto wrap_route(
    uWS::HttpResponse<true> *const response_handler,
    uWS::HttpRequest *const request_handler,
    const sourcemeta::hydra::http::Server::ErrorCallback &error,
    const sourcemeta::hydra::http::Server::RouteCallback &callback) noexcept
    -> void {
  assert(error);
  assert(callback);
  assert(response_handler);
  assert(request_handler);

  // These should never throw, otherwise we cannot even react to errors
  sourcemeta::hydra::http::ServerLogger logger;
  sourcemeta::hydra::http::ServerResponse response{response_handler};
  const sourcemeta::hydra::http::ServerRequest request{request_handler};

  try {
    callback(logger, request, response);
  } catch (...) {
    error(std::current_exception(), logger, request, response);
  }

  std::ostringstream line;
  line << response.status() << ' ' << request.method() << ' ' << request.path();
  logger << line.str();
}

static auto
default_handler(const sourcemeta::hydra::http::ServerLogger &,
                const sourcemeta::hydra::http::ServerRequest &,
                sourcemeta::hydra::http::ServerResponse &response) -> void {
  response.status(sourcemeta::hydra::http::Status::NOT_IMPLEMENTED);
  response.end();
}

static auto default_error_handler(
    std::exception_ptr error, const sourcemeta::hydra::http::ServerLogger &,
    const sourcemeta::hydra::http::ServerRequest &,
    sourcemeta::hydra::http::ServerResponse &response) -> void {
  assert(error);
  response.status(sourcemeta::hydra::http::Status::INTERNAL_SERVER_ERROR);
  try {
    std::rethrow_exception(error);
  } catch (const std::exception &exception) {
    response.end(exception.what());
  }
}

namespace sourcemeta::hydra::http {

Server::Server()
    : routes{}, fallback{default_handler},
      error_handler{default_error_handler} {}

auto Server::route(const Method method, std::string &&path,
                   RouteCallback &&callback) -> void {
  this->routes.emplace_back(method, std::move(path), std::move(callback));
}

auto Server::otherwise(RouteCallback &&callback) -> void {
  this->fallback = std::move(callback);
}

auto Server::error(ErrorCallback &&callback) -> void {
  this->error_handler = std::move(callback);
}

auto Server::run(const std::uint32_t port) const -> int {
  uWS::LocalCluster({}, [this, port](uWS::SSLApp &app) -> void {

#define UWS_CALLBACK(callback_name)                                            \
  [&](auto *const response_handler,                                            \
      auto *const request_handler) noexcept -> void {                          \
    wrap_route(response_handler, request_handler, this->error_handler,         \
               (callback_name));                                               \
  }
    for (const auto &entry : this->routes) {
      switch (std::get<0>(entry)) {
        case Method::GET:
          app.get(std::get<1>(entry), UWS_CALLBACK(std::get<2>(entry)));
          break;
        case Method::HEAD:
          app.head(std::get<1>(entry), UWS_CALLBACK(std::get<2>(entry)));
          break;
        case Method::POST:
          app.post(std::get<1>(entry), UWS_CALLBACK(std::get<2>(entry)));
          break;
        case Method::PUT:
          app.put(std::get<1>(entry), UWS_CALLBACK(std::get<2>(entry)));
          break;
        case Method::DELETE:
          app.del(std::get<1>(entry), UWS_CALLBACK(std::get<2>(entry)));
          break;
        case Method::CONNECT:
          app.connect(std::get<1>(entry), UWS_CALLBACK(std::get<2>(entry)));
          break;
        case Method::OPTIONS:
          app.options(std::get<1>(entry), UWS_CALLBACK(std::get<2>(entry)));
          break;
        case Method::TRACE:
          app.trace(std::get<1>(entry), UWS_CALLBACK(std::get<2>(entry)));
          break;
        case Method::PATCH:
          app.patch(std::get<1>(entry), UWS_CALLBACK(std::get<2>(entry)));
          break;
      }
    }

    assert(this->fallback);
    app.any("/*", UWS_CALLBACK(this->fallback));
#undef UWS_CALLBACK

    app.listen(static_cast<int>(port),
               [port, this](us_listen_socket_t *const socket) -> void {
                 if (socket) {
                   const auto socket_port = us_socket_local_port(
                       true, reinterpret_cast<struct us_socket_t *>(socket));
                   assert(socket_port > 0);
                   assert(port == static_cast<std::uint32_t>(socket_port));
                   this->logger
                       << "Listening on port " + std::to_string(socket_port);
                 } else {
                   this->logger
                       << "Failed to listen on port " + std::to_string(port);
                 }
               });
  });

  // This method only returns on failure
  this->logger << "Failed to listen on port " + std::to_string(port);
  return EXIT_FAILURE;
}

} // namespace sourcemeta::hydra::http
