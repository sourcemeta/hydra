#ifndef SOURCEMETA_HYDRA_HTTP_STREAM_H
#define SOURCEMETA_HYDRA_HTTP_STREAM_H

#if defined(__Unikraft__)
#define SOURCEMETA_HYDRA_HTTP_EXPORT
#else
#include "http_export.h"
#endif

#include <sourcemeta/hydra/http_method.h>
#include <sourcemeta/hydra/http_status.h>

#include <cstdint>     // std::uint8_t
#include <functional>  // std::function
#include <future>      // std::future
#include <memory>      // std::unique_ptr
#include <span>        // std::span
#include <string>      // std::string
#include <string_view> // std::string_view

namespace sourcemeta::hydra::http {

/// @ingroup http
/// This class is used to perform a streaming HTTP request.
class SOURCEMETA_HYDRA_HTTP_EXPORT Stream {
public:
  /// Construct a streaming HTTP request to a given URL. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <iostream>
  ///
  /// sourcemeta::hydra::http::Stream request{"https://www.example.com"};
  /// request.method(sourcemeta::hydra::http::Method::GET);
  ///
  /// request.on_data([](const sourcemeta::hydra::http::Status status,
  ///                    std::span<const std::uint8_t> buffer) noexcept {
  ///   std::cerr << "Code: " << status << "\n";
  ///
  ///   // Copy to standard output
  ///   for (const auto byte : buffer) {
  ///     std::cout << static_cast<char>(byte);
  ///   }
  /// });
  ///
  /// request.on_header([](const sourcemeta::hydra::http::Status status,
  ///                      std::string_view key,
  ///                      std::string_view value) noexcept {
  ///   std::cerr << "Code: " << status << "\n";
  ///
  ///   // Print the incoming headers
  ///   std::cout << key << " -> " << value << "\n";
  /// });
  ///
  /// request.send().wait();
  /// ```
  Stream(std::string url);

  /// Move an instance of this class. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <utility>
  ///
  /// sourcemeta::hydra::http::Stream request{"https://www.example.com"};
  /// sourcemeta::hydra::http::Stream new_request{std::move(request)};
  /// ```
  Stream(Stream &&other) noexcept;

  /// Move an instance of this class. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <utility>
  ///
  /// sourcemeta::hydra::http::Stream request{"https://www.example.com"};
  /// sourcemeta::hydra::http::Stream new_request = std::move(request);
  /// ```
  auto operator=(Stream &&other) noexcept -> Stream &;

  // While technically possible, copy semantics are not very useful here
  // Also, not worth documenting these.
#if !defined(DOXYGEN)
  Stream(const Stream &other) = delete;
  auto operator=(const Stream &other) -> Stream & = delete;
#endif

  /// Destruct an instance of this class.
  ~Stream();

  /// Specify the HTTP method to use for the request. If not set, it defauls to
  /// `GET`. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <iostream>
  ///
  /// sourcemeta::hydra::http::Stream request{"https://www.example.com"};
  ///
  /// // Send a POST request
  /// request.method(sourcemeta::hydra::http::Method::POST);
  ///
  /// request.on_data([](const sourcemeta::hydra::http::Status status,
  ///                    std::span<const std::uint8_t> buffer) noexcept {
  ///   std::cerr << "Code: " << status << "\n";
  ///
  ///   // Copy to standard output
  ///   for (const auto byte : buffer) {
  ///     std::cout << static_cast<char>(byte);
  ///   }
  /// });
  ///
  /// request.send().wait();
  /// ```
  auto method(const Method method) noexcept -> void;

  /// Set an HTTP request header. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <iostream>
  ///
  /// sourcemeta::hydra::http::Stream request{"https://www.example.com"};
  /// request.header("X-Send-With", "Hydra");
  ///
  /// request.on_data([](const sourcemeta::hydra::http::Status status,
  ///                    std::span<const std::uint8_t> buffer) noexcept {
  ///   std::cerr << "Code: " << status << "\n";
  ///
  ///   // Copy to standard output
  ///   for (const auto byte : buffer) {
  ///     std::cout << static_cast<char>(byte);
  ///   }
  /// });
  ///
  /// request.send().wait();
  /// ```
  auto header(std::string_view key, std::string_view value) -> void;

  /// Set an HTTP request header whose value is an integer. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <iostream>
  ///
  /// sourcemeta::hydra::http::Stream request{"https://www.example.com"};
  /// request.header("X-Favourite-Number", 3);
  ///
  /// request.on_data([](const sourcemeta::hydra::http::Status status,
  ///                    std::span<const std::uint8_t> buffer) noexcept {
  ///   std::cerr << "Code: " << status << "\n";
  ///
  ///   // Copy to standard output
  ///   for (const auto byte : buffer) {
  ///     std::cout << static_cast<char>(byte);
  ///   }
  /// });
  ///
  /// request.send().wait();
  /// ```
  auto header(std::string_view key, int value) -> void;

  /// Sign the request using Amazon's Signature v4. For example, to send a
  /// request to an S3-compatible API:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  ///
  /// sourcemeta::hydra::http::Stream request{"https://www.example.com"};
  /// request.aws_sigv4("s3", "us-east-1", "1234567", "my-secret");
  /// request.send().wait();
  /// ```
  ///
  /// See
  /// https://docs.aws.amazon.com/AmazonS3/latest/API/sig-v4-authenticating-requests.html
  auto aws_sigv4(std::string_view service, std::string_view region,
                 std::string_view access_key, std::string_view secret_key)
      -> void;

  /// Perform the streaming HTTP request, resolving the response status code.
  /// For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <iostream>
  /// #include <cassert>
  ///
  /// sourcemeta::hydra::http::Stream request{"https://www.example.com"};
  /// request.method(sourcemeta::hydra::http::Method::GET);
  ///
  /// request.on_data([](const sourcemeta::hydra::http::Status status,
  ///                    std::span<const std::uint8_t> buffer) noexcept {
  ///   std::cerr << "Code: " << status << "\n";
  ///
  ///   // Copy to standard output
  ///   for (const auto byte : buffer) {
  ///     std::cout << static_cast<char>(byte);
  ///   }
  /// });
  ///
  /// request.on_header([](const sourcemeta::hydra::http::Status status,
  ///                      std::string_view key,
  ///                      std::string_view value) noexcept {
  ///   std::cerr << "Code: " << status << "\n";
  ///
  ///   // Print the incoming headers
  ///   std::cout << key << " -> " << value << "\n";
  /// });
  ///
  /// auto status{request.send().get()};
  /// assert(status == sourcemeta::hydra::http::Status::OK);
  auto send() -> std::future<Status>;

  using DataCallback =
      std::function<void(const Status, std::span<const std::uint8_t>)>;
  using HeaderCallback =
      std::function<void(const Status, std::string_view, std::string_view)>;

  /// Set a function that gets called every time there is new data to process.
  /// The callback gets passed the response status code and a buffer. Make sure
  /// your callback does not throw exceptions, as it may result in undefined
  /// behavior. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <iostream>
  ///
  /// sourcemeta::hydra::http::Stream request{"https://www.example.com"};
  ///
  /// request.on_data([](const sourcemeta::hydra::http::Status status,
  ///                    std::span<const std::uint8_t> buffer) noexcept {
  ///   std::cerr << "Code: " << status << "\n";
  ///
  ///   // Copy to standard output
  ///   for (const auto byte : buffer) {
  ///     std::cout << static_cast<char>(byte);
  ///   }
  /// });
  ///
  /// request.send().wait();
  /// ```
  auto on_data(DataCallback callback) noexcept -> void;

  /// Set a function that gets called every time there is a new response header
  /// to process. The callback gets passed the response status code, and the
  /// header key and value. Make sure your callback does not throw exceptions,
  /// as it may result in undefined behavior. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/hydra/http.h>
  /// #include <iostream>
  ///
  /// sourcemeta::hydra::http::Stream request{"https://www.example.com"};
  ///
  /// request.on_header([](const sourcemeta::hydra::http::Status status,
  ///                      std::string_view key,
  ///                      std::string_view value) noexcept {
  ///   std::cerr << "Code: " << status << "\n";
  ///
  ///   // Print the incoming headers
  ///   std::cout << key << " -> " << value << "\n";
  /// });
  ///
  /// request.send().wait();
  /// ```
  auto on_header(HeaderCallback callback) noexcept -> void;

private:
  struct Internal;

  // No need to make this private, as the contents of `Internal`
  // are already hidden with the PIMPL idiom.
public:
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif
  std::unique_ptr<Internal> internal;
#if defined(_MSC_VER)
#pragma warning(default : 4251)
#endif
};

} // namespace sourcemeta::hydra::http

#endif
