#include <sourcemeta/hydra/httpserver_request.h>

#include "uwebsockets.h"

#include <cassert>   // assert
#include <stdexcept> // std::invalid_argument

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
    -> std::optional<std::vector<HeaderListElement>> {
  const auto header_string{this->header(key)};
  if (!header_string.has_value()) {
    return std::nullopt;
  }

  return sourcemeta::hydra::http::header_list(header_string.value());
}

auto ServerRequest::header_gmt(std::string_view key) const
    -> std::optional<std::chrono::system_clock::time_point> {
  const auto header_string{this->header(key)};
  if (!header_string.has_value()) {
    return std::nullopt;
  }

  return sourcemeta::hydra::http::header_gmt(header_string.value());
}

auto ServerRequest::header_if_modified_since(
    const std::chrono::system_clock::time_point last_modified) const -> bool {
  // `If-Modified-Since` can only be used with a `GET` or `HEAD`.
  // See
  // https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/If-Modified-Since
  if (this->method() != Method::GET && this->method() != Method::HEAD) {
    return true;
  }

  try {
    const auto if_modified_since{this->header_gmt("if-modified-since")};
    // If the client didn't express a modification baseline to compare to, then
    // we just tell it that it has been modified
    if (!if_modified_since.has_value()) {
      return true;
    }

    return if_modified_since.value() < last_modified;
    // If there is an error parsing the `If-Modified-Since` timestamp, don't
    // abort, but lean on the safe side: the requested resource has been
    // modified
  } catch (const std::invalid_argument &) {
    return true;
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

auto ServerRequest::path() const -> std::string {
  return std::string{this->internal->handler->getUrl()};
}

auto ServerRequest::parameter(const std::uint8_t index) const -> std::string {
  return std::string{this->internal->handler->getParameter(index)};
}

} // namespace sourcemeta::hydra::http
