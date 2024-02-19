#include <sourcemeta/hydra/http_method.h>

#include <cassert>   // assert
#include <stdexcept> // std::invalid_argument

namespace sourcemeta::hydra::http {

auto operator<<(std::ostream &stream, const Method method) -> std::ostream & {
  switch (method) {
    case Method::GET:
      stream << "GET";
      return stream;
    case Method::HEAD:
      stream << "HEAD";
      return stream;
    case Method::POST:
      stream << "POST";
      return stream;
    case Method::PUT:
      stream << "PUT";
      return stream;
    case Method::DELETE:
      stream << "DELETE";
      return stream;
    case Method::CONNECT:
      stream << "CONNECT";
      return stream;
    case Method::OPTIONS:
      stream << "OPTIONS";
      return stream;
    case Method::TRACE:
      stream << "TRACE";
      return stream;
    case Method::PATCH:
      stream << "PATCH";
      return stream;

    // Should never happen
    default:
      assert(false);
      return stream;
  }
}

auto to_method(std::string_view method) -> Method {
  if (method == "GET") {
    return Method::GET;
  } else if (method == "HEAD") {
    return Method::HEAD;
  } else if (method == "POST") {
    return Method::POST;
  } else if (method == "PUT") {
    return Method::PUT;
  } else if (method == "DELETE") {
    return Method::DELETE;
  } else if (method == "CONNECT") {
    return Method::CONNECT;
  } else if (method == "OPTIONS") {
    return Method::OPTIONS;
  } else if (method == "TRACE") {
    return Method::TRACE;
  } else if (method == "PATCH") {
    return Method::PATCH;
  } else {
    throw std::invalid_argument("Invalid HTTP method");
  }
}

} // namespace sourcemeta::hydra::http
