#ifndef SOURCEMETA_HYDRA_HTTP_RESPONSE_H
#define SOURCEMETA_HYDRA_HTTP_RESPONSE_H

#ifndef SOURCEMETA_HYDRA_HTTP_EXPORT
#include <sourcemeta/hydra/http_export.h>
#endif

#include <sourcemeta/hydra/http_status.h>

#include <optional>      // std::optional
#include <sstream>       // std::ostringstream, std::istringstream
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace sourcemeta::hydra::http {

/// @ingroup http
/// This class represents a non-streaming HTTP response.
class SOURCEMETA_HYDRA_HTTP_EXPORT ClientResponse {
public:
  // We don't want to document this internal constructor
#if !defined(DOXYGEN)
  ClientResponse(const Status status,
                 std::unordered_map<std::string, std::string> &&headers,
                 std::ostringstream &&stream);
#endif

  /// Get the status code of the response. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::ClientRequest request{"https://www.example.com"};
  /// request.method(sourcemeta::hydra::http::Method::GET);
  /// sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  /// assert(response.status() == sourcemeta::hydra::http::Status::OK);
  /// ```
  auto status() const noexcept -> Status;

  /// Get the value of a given response header, if any. Remember that you
  /// must express your desire of capturing the response headers you are
  /// interest in when performing the request, using
  /// sourcemeta::hydra::http::ClientRequest::capture.
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::ClientRequest request{"https://www.example.com"};
  /// request.method(sourcemeta::hydra::http::Method::GET);
  ///
  /// // Remember to capture the headers you are interested in!
  /// request.capture("content-type");
  ///
  /// sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  /// assert(response.header("content-type").has_value());
  /// assert(response.header("content-type").value()
  ///   == "text/html; charset=UTF-8");
  /// ```
  auto header(const std::string &key) const -> std::optional<std::string>;

  /// Get a container for all the captured response headers. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <iostream>
  ///
  /// sourcemeta::hydra::http::ClientRequest request{"https://www.example.com"};
  /// request.method(sourcemeta::hydra::http::Method::GET);
  ///
  /// // Capture all headers
  /// request.capture();
  ///
  /// sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  /// for (const auto &[ key, value ]) {
  ///   std::cout << key << " -> " << value << "\n";
  /// }
  /// ```
  auto headers() const -> const std::unordered_map<std::string, std::string> &;

  /// Check whether a response has a body to consume or not. A request made
  /// with the `HEAD` HTTP method is almost always empty. Remember to always
  /// check if a response is empty before calling
  /// sourcemeta::hydra::http::ClientResponse::body.
  ///
  /// For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::ClientRequest request{"https://www.example.com"};
  /// request.method(sourcemeta::hydra::http::Method::HEAD);
  /// sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  /// assert(response.empty());
  /// ```
  auto empty() noexcept -> bool;

  /// Obtain the response body as an input stream. Getting the response body of
  /// an empty response is undefined behavior. Remember to check for this case
  /// using sourcemeta::hydra::http::ClientResponse::empty. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <cassert>
  /// #include <iostream>
  /// #include <iterator>
  ///
  /// sourcemeta::hydra::http::ClientRequest request{"https://www.example.com"};
  /// request.method(sourcemeta::hydra::http::Method::GET);
  /// sourcemeta::hydra::http::ClientResponse response{request.send().get()};
  /// assert(response.status() == sourcemeta::hydra::http::Status::OK);
  ///
  /// if (!response.empty()) {
  ///   // Copy response body to standard output
  ///   std::copy(std::istreambuf_iterator<char>(response.body()),
  ///             std::istreambuf_iterator<char>(),
  ///             std::ostreambuf_iterator<char>(std::cout));
  ///   std::cout << "\n";
  /// }
  /// ```
  auto body() -> std::istringstream &;

private:
  Status status_;
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif
  std::unordered_map<std::string, std::string> headers_;
  std::istringstream stream_;
#if defined(_MSC_VER)
#pragma warning(default : 4251)
#endif
};

} // namespace sourcemeta::hydra::http

#endif
