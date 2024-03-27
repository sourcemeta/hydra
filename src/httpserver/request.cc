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

auto ServerRequest::header_list(std::string_view key) const
    -> std::optional<std::vector<std::string>> {
  const auto header_string{this->header(key)};
  if (!header_string.has_value()) {
    return std::nullopt;
  }

  return sourcemeta::hydra::http::header_list(header_string.value());
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

auto ServerRequest::path() const -> std::string {
  return std::string{this->internal->handler->getUrl()};
}

auto ServerRequest::parameter(const std::uint8_t index) const -> std::string {
  return std::string{this->internal->handler->getParameter(index)};
}

} // namespace sourcemeta::hydra::http
