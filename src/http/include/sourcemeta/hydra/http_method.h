#ifndef SOURCEMETA_HYDRA_HTTP_METHOD_H
#define SOURCEMETA_HYDRA_HTTP_METHOD_H

namespace sourcemeta::hydra::http {

/// @ingroup http
/// The list of possible HTTP methods.
enum class Method {
  GET,
  HEAD,
  POST,
  PUT,
  DELETE,
  CONNECT,
  OPTIONS,
  TRACE,
  PATCH
};

} // namespace sourcemeta::hydra::http

#endif
