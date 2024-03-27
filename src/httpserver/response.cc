#include <sourcemeta/hydra/httpserver_response.h>

#include "uwebsockets.h"

#include <cassert> // assert
#include <sstream> // std::ostringstream

namespace sourcemeta::hydra::http {

struct ServerResponse::Internal {
  uWS::HttpResponse<true> *handler;
};

ServerResponse::ServerResponse(void *const handler)
    : internal{std::make_unique<ServerResponse::Internal>()} {
  assert(handler);
  this->internal->handler = static_cast<uWS::HttpResponse<true> *>(handler);
}

ServerResponse::~ServerResponse() {}

auto ServerResponse::status(const Status status_code) -> void {
  std::ostringstream code_string;
  code_string << status_code;
  this->internal->handler->writeStatus(code_string.str());
  this->code = status_code;
}

auto ServerResponse::status() const -> Status { return this->code; }

auto ServerResponse::header(std::string_view key,
                            std::string_view value) -> void {
  this->internal->handler->writeHeader(key, value);
}

auto ServerResponse::end(const std::string_view message) -> void {
  this->internal->handler->end(message);
}

auto ServerResponse::end() -> void { this->internal->handler->end(); }

} // namespace sourcemeta::hydra::http
