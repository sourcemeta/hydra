#include <sourcemeta/hydra/http_method.h>
#include <sourcemeta/hydra/http_request.h>
#include <sourcemeta/hydra/http_response.h>
#include <sourcemeta/hydra/http_status.h>

#include <algorithm>        // std::copy
#include <cstdint>          // std::uint8_t
#include <future>           // std::future, std::promise
#include <initializer_list> // std::initializer_list
#include <iterator>         // std::ostream_iterator
#include <map>              // std::map
#include <span>             // std::span
#include <sstream>          // std::ostringstream
#include <string>           // std::string
#include <string_view>      // std::string_view
#include <utility>          // std::move

namespace sourcemeta::hydra::http {

Request::Request(std::string url) : stream{std::move(url)} {}

auto Request::method(const Method method) noexcept -> void {
  this->stream.method(method);
}

auto Request::capture(std::string header) -> void {
  this->capture_all_ = false;
  this->capture_.insert(std::move(header));
}

auto Request::capture(std::initializer_list<std::string> headers) -> void {
  this->capture_all_ = false;
  this->capture_.insert(headers);
}

auto Request::capture() -> void { this->capture_all_ = true; }

auto Request::header(std::string_view key, std::string_view value) -> void {
  this->stream.header(key, value);
}

auto Request::header(std::string_view key, int value) -> void {
  this->stream.header(key, value);
}

auto Request::send() -> std::future<Response> {
  std::ostringstream output;
  this->stream.on_data(
      [&output](const Status, std::span<const std::uint8_t> buffer) noexcept {
        std::copy(buffer.begin(), buffer.end(),
                  std::ostream_iterator<char>(output));
      });

  std::map<std::string, std::string> headers;
  this->stream.on_header([&headers, this](const Status, std::string_view key,
                                          std::string_view value) noexcept {
    std::string header{key};
    if (this->capture_.contains(header) || this->capture_all_) {
      headers.insert_or_assign(std::move(header), std::string{value});
    }
  });

  std::promise<Response> response;
  response.set_value(
      {this->stream.send().get(), std::move(headers), std::move(output)});
  return response.get_future();
}

} // namespace sourcemeta::hydra::http
