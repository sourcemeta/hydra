#ifndef SOURCEMETA_HYDRA_TEST_BUCKET_ENVIRONMENT_H_
#define SOURCEMETA_HYDRA_TEST_BUCKET_ENVIRONMENT_H_

#include <cstdlib>  // std::exit, std::getenv
#include <iostream> // std::cerr
#include <string>   // std::string

static const char *const SOURCEMETA_HYDRA_TEST_BUCKET_BASE_URL =
    std::getenv("SOURCEMETA_HYDRA_TEST_BUCKET_BASE_URL");
static const char *const SOURCEMETA_HYDRA_TEST_BUCKET_REGION =
    std::getenv("SOURCEMETA_HYDRA_TEST_BUCKET_REGION");
static const char *const SOURCEMETA_HYDRA_TEST_BUCKET_ACCESS_KEY =
    std::getenv("SOURCEMETA_HYDRA_TEST_BUCKET_ACCESS_KEY");
static const char *const SOURCEMETA_HYDRA_TEST_BUCKET_SECRET_KEY =
    std::getenv("SOURCEMETA_HYDRA_TEST_BUCKET_SECRET_KEY");

inline auto BUCKET_BASE_URL() -> const std::string & {
  if (!SOURCEMETA_HYDRA_TEST_BUCKET_BASE_URL) {
    std::cerr << "Missing environment variable: "
                 "SOURCEMETA_HYDRA_TEST_BUCKET_BASE_URL\n";
    std::exit(1);
  }

  static std::string BASE_URL{SOURCEMETA_HYDRA_TEST_BUCKET_BASE_URL};
  std::cerr << "SOURCEMETA_HYDRA_TEST_BUCKET_BASE_URL: " << BASE_URL << "\n";
  return BASE_URL;
}

inline auto BUCKET_REGION() -> const std::string & {
  if (!SOURCEMETA_HYDRA_TEST_BUCKET_REGION) {
    std::cerr << "Missing environment variable: "
                 "SOURCEMETA_HYDRA_TEST_BUCKET_REGION\n";
    std::exit(1);
  }

  static std::string REGION{SOURCEMETA_HYDRA_TEST_BUCKET_REGION};
  std::cerr << "SOURCEMETA_HYDRA_TEST_BUCKET_REGION: " << REGION << "\n";
  return REGION;
}

inline auto BUCKET_ACCESS_KEY() -> const std::string & {
  if (!SOURCEMETA_HYDRA_TEST_BUCKET_ACCESS_KEY) {
    std::cerr << "Missing environment variable: "
                 "SOURCEMETA_HYDRA_TEST_BUCKET_ACCESS_KEY\n";
    std::exit(1);
  }

  static std::string ACCESS_KEY{SOURCEMETA_HYDRA_TEST_BUCKET_ACCESS_KEY};
  std::cerr << "SOURCEMETA_HYDRA_TEST_BUCKET_ACCESS_KEY: " << ACCESS_KEY
            << "\n";
  return ACCESS_KEY;
}

inline auto BUCKET_SECRET_KEY() -> const std::string & {
  if (!SOURCEMETA_HYDRA_TEST_BUCKET_SECRET_KEY) {
    std::cerr << "Missing environment variable: "
                 "SOURCEMETA_HYDRA_TEST_BUCKET_SECRET_KEY\n";
    std::exit(1);
  }

  static std::string SECRET_KEY{SOURCEMETA_HYDRA_TEST_BUCKET_SECRET_KEY};
  std::cerr << "SOURCEMETA_HYDRA_TEST_BUCKET_SECRET_KEY: " << SECRET_KEY
            << "\n";
  return SECRET_KEY;
}

#endif
