#ifndef SOURCEMETA_HYDRA_TEST_HTTP_BASE_URL_H_
#define SOURCEMETA_HYDRA_TEST_HTTP_BASE_URL_H_

#include <cstdlib>  // std::exit, std::getenv
#include <iostream> // std::cerr
#include <string>   // std::string

static const char *const SOURCEMETA_HYDRA_TEST_BASE_URL =
    std::getenv("SOURCEMETA_HYDRA_TEST_BASE_URL");

inline auto HTTP_BASE_URL() -> const std::string & {
  if (!SOURCEMETA_HYDRA_TEST_BASE_URL) {
    std::cerr
        << "Missing environment variable: SOURCEMETA_HYDRA_TEST_BASE_URL\n";
    std::exit(1);
  }

  static std::string BASE_URL{SOURCEMETA_HYDRA_TEST_BASE_URL};
  std::cerr << "Test HTTP server base URL: " << BASE_URL << "\n";
  return BASE_URL;
}

#endif
