#include <sourcemeta/hydra/bucket.h>
#include <sourcemeta/hydra/crypto.h>
#include <sourcemeta/hydra/httpclient.h>

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // std::cout

auto main() -> int {
  std::cout << sourcemeta::hydra::http::Status::OK << "\n";
  return EXIT_SUCCESS;
}
