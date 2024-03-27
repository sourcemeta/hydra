#ifndef SOURCEMETA_HYDRA_HTTP_HEADER_H
#define SOURCEMETA_HYDRA_HTTP_HEADER_H

#if defined(__Unikraft__)
#define SOURCEMETA_HYDRA_HTTP_EXPORT
#else
#include "http_export.h"
#endif

#include <chrono> // std::chrono::system_clock::time_point
#include <string> // std::string

namespace sourcemeta::hydra::http {

/// @ingroup http
/// Parse a header that consists of a GMT timestamp. For example:
///
/// ```cpp
/// #include <sourcemeta/hydra/http.h>
/// #include <cassert>
///
/// const auto point{
///   sourcemeta::hydra::http::header_gmt("Wed, 21 Oct 2015 11:28:00 GMT")};
/// ```
auto SOURCEMETA_HYDRA_HTTP_EXPORT header_gmt(const std::string &value)
    -> std::chrono::system_clock::time_point;

} // namespace sourcemeta::hydra::http

#endif
