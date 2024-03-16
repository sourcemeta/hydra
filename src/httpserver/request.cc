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

} // namespace sourcemeta::hydra::http
