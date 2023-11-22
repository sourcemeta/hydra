#include <sourcemeta/hydra/http.h>

#include <cassert>
#include <iostream>
#include <iterator>

int main() {
  sourcemeta::hydra::http::Request request{"https://www.example.com"};
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::Response response{request.send().get()};

  std::cerr << "CODE: " << response.status() << "\n";
  std::cerr << "DATA:\n";

  if (!response.empty()) {
    // Copy response body to standard output
    std::copy(std::istreambuf_iterator<char>(response.body()),
              std::istreambuf_iterator<char>(),
              std::ostreambuf_iterator<char>(std::cout));
    std::cout << "\n";
  }

  return 0;
}
