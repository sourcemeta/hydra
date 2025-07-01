#include <sourcemeta/hydra/http.h>

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // std::cout

auto main() -> int {
  std::cout << sourcemeta::hydra::http::Status::OK << "\n";
  return EXIT_SUCCESS;
}
