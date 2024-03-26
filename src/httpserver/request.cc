#include <sourcemeta/hydra/httpserver_request.h>

#include "uwebsockets.h"

#include <cassert> // assert

namespace sourcemeta::hydra::http {

struct ServerRequest::Internal {
  uWS::HttpRequest *handler;
};

ServerRequest::ServerRequest(void *const handler)
    : internal{std::make_unique<ServerRequest::Internal>()} {
  assert(handler);
  this->internal->handler = static_cast<uWS::HttpRequest *>(handler);
}

ServerRequest::~ServerRequest() {}

auto ServerRequest::method() const -> Method {
  return to_method(this->internal->handler->getMethod());
}

auto ServerRequest::header(std::string_view key) const
    -> std::optional<std::string> {
  const std::string_view value{this->internal->handler->getHeader(key)};
  if (value.empty()) {
    return std::nullopt;
  } else {
    return std::string{value};
  }
}

auto ServerRequest::query(std::string_view key) const
    -> std::optional<std::string> {
  const std::string_view value{this->internal->handler->getQuery(key)};
  if (value.empty()) {
    return std::nullopt;
  } else {
    return std::string{value};
  }
}

} // namespace sourcemeta::hydra::http
