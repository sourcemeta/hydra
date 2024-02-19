#ifndef SOURCEMETA_HYDRA_HTTP_REQUEST_H
#define SOURCEMETA_HYDRA_HTTP_REQUEST_H

#if defined(__Unikraft__)
#define SOURCEMETA_HYDRA_HTTP_EXPORT
#else
#include "http_export.h"
#endif

#include <sourcemeta/hydra/http_method.h>
#include <sourcemeta/hydra/http_response.h>
#include <sourcemeta/hydra/http_stream.h>

#include <future>           // std::future
#include <initializer_list> // std::initializer_list
#include <set>              // std::set
#include <string>           // std::string
#include <string_view>      // std::string_view

namespace sourcemeta::hydra::http {

// TODO: Support passing a request body
/// @ingroup http
/// This class is used to perform a non-streaming HTTP request.
class SOURCEMETA_HYDRA_HTTP_EXPORT Request {
public:
  /// Construct an HTTP request to a given URL. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Request request{"https://www.example.com"};
  /// request.method(sourcemeta::hydra::http::Method::GET);
  /// sourcemeta::hydra::http::Response response{request.send().get()};
  /// assert(response.status() == sourcemeta::hydra::http::Status::OK);
  /// ```
  Request(std::string url);

  /// Specify the HTTP method to use for the request. If not set, it defauls to
  /// `GET`. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Request request{"https://www.example.com"};
  ///
  /// // Send a POST request
  /// request.method(sourcemeta::hydra::http::Method::POST);
  ///
  /// sourcemeta::hydra::http::Response response{request.send().get()};
  /// assert(response.status() == sourcemeta::hydra::http::Status::OK);
  /// ```
  auto method(const Method method) noexcept -> void;

  /// Express a desire of capturing a specific response header, if sent by the
  /// server.
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Request request{"https://www.example.com"};
  /// request.method(sourcemeta::hydra::http::Method::GET);
  /// request.capture("content-type");
  /// sourcemeta::hydra::http::Response response{request.send().get()};
  /// assert(response.header("content-type").has_value());
  /// assert(response.header("content-type").value()
  ///   == "text/html; charset=UTF-8");
  /// ```
  auto capture(std::string header) -> void;

  /// Express a desire of capturing a set of response headers, if sent by the
  /// server.
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Request request{"https://www.example.com"};
  /// request.method(sourcemeta::hydra::http::Method::GET);
  /// request.capture({ "content-type", "content-encoding", "x-foo" });
  /// sourcemeta::hydra::http::Response response{request.send().get()};
  /// assert(response.header("content-type").has_value());
  /// assert(response.header("content-encoding").has_value());
  /// assert(!response.header("x-foo").has_value());
  /// ```
  auto capture(std::initializer_list<std::string> headers) -> void;

  /// Express a desire of capturing every response headers. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Request request{"https://www.example.com"};
  /// request.method(sourcemeta::hydra::http::Method::GET);
  /// request.capture();
  /// sourcemeta::hydra::http::Response response{request.send().get()};
  /// assert(response.header("content-type").has_value());
  /// assert(response.header("content-encoding").has_value());
  /// ```
  auto capture() -> void;

  /// Set an HTTP request header. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Request request{"https://www.example.com"};
  /// request.header("X-Send-With", "Hydra");
  /// sourcemeta::hydra::http::Response response{request.send().get()};
  /// assert(response.status() == sourcemeta::hydra::http::Status::OK);
  /// ```
  auto header(std::string_view key, std::string_view value) -> void;

  /// Set an HTTP request header whose value is an integer. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Request request{"https://www.example.com"};
  /// request.header("X-Favourite-Number", 3);
  /// sourcemeta::hydra::http::Response response{request.send().get()};
  /// assert(response.status() == sourcemeta::hydra::http::Status::OK);
  /// ```
  auto header(std::string_view key, int value) -> void;

  /// Sign the request using Amazon's Signature v4. For example, to send a
  /// request to an S3-compatible API:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Request request{"https://www.example.com"};
  /// request.aws_sigv4("s3", "us-east-1", "1234567", "my-secret");
  /// sourcemeta::hydra::http::Response response{request.send().get()};
  /// assert(response.status() == sourcemeta::hydra::http::Status::OK);
  /// ```
  ///
  /// See
  /// https://docs.aws.amazon.com/AmazonS3/latest/API/sig-v4-authenticating-requests.html
  auto aws_sigv4(std::string_view service, std::string_view region,
                 std::string_view access_key, std::string_view secret_key)
      -> void;

  /// Perform the HTTP request. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Request request{"https://www.example.com"};
  /// request.method(sourcemeta::hydra::http::Method::GET);
  /// sourcemeta::hydra::http::Response response{request.send().get()};
  /// assert(response.status() == sourcemeta::hydra::http::Status::OK);
  /// ```
  auto send() -> std::future<Response>;

private:
  Stream stream;
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif
  std::set<std::string> capture_;
#if defined(_MSC_VER)
#pragma warning(default : 4251)
#endif
  bool capture_all_{false};
};

} // namespace sourcemeta::hydra::http

#endif
