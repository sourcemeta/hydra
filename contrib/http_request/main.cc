#include <cstdlib>   // EXIT_SUCCESS, EXIT_FAILURE
#include <exception> // std::exception
#include <iostream>  // std::cout, std::cerr

#include <sourcemeta/hydra/http.h>

int main() {
  try {
    sourcemeta::hydra::http::Request request{"https://postman-echo.com/get"};
    request.method(sourcemeta::hydra::http::Method::GET);
    request.header("X-Foo", "bar");
    request.capture({"content-type"});

    sourcemeta::hydra::http::Response response{request.send().get()};
    std::cout << "CODE: " << response.status() << "\n";

    const auto contentType{response.header("content-type")};
    if (contentType.has_value()) {
      std::cout << "HEADER: Content-Type => " << contentType.value() << "\n";
    }

    std::copy(std::istreambuf_iterator<char>(response.body()),
              std::istreambuf_iterator<char>(),
              std::ostreambuf_iterator<char>(std::cout));
    std::cout << "\n";

    return EXIT_SUCCESS;
  } catch (const std::exception &error) {
    std::cerr << "Error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }
}
