#include <cstdlib>   // EXIT_SUCCESS, EXIT_FAILURE
#include <exception> // std::exception
#include <iostream>  // std::cout, std::cerr

#include <sourcemeta/hydra/http.h>

int main() {
  try {
    sourcemeta::hydra::http::Stream request{"https://postman-echo.com/get"};
    request.method(sourcemeta::hydra::http::Method::GET);
    request.header("X-Foo", "bar");

    request.on_data([](const sourcemeta::hydra::http::Status status,
                       std::span<const std::uint8_t> buffer) noexcept {
      std::cerr << "==== (CODE: " << status << ") ON DATA ==========\n";
      for (const auto byte : buffer) {
        std::cout << static_cast<char>(byte);
      }
      std::cout << "\n";
    });

    request.on_header([](const sourcemeta::hydra::http::Status status,
                         std::string_view key,
                         std::string_view value) noexcept {
      std::cerr << "==== (CODE: " << status << ") ON HEADER ========\n";
      std::cout << key << " -> " << value << "\n";
    });

    request.send().wait();

    return EXIT_SUCCESS;
  } catch (const std::exception &error) {
    std::cerr << "Error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }
}
