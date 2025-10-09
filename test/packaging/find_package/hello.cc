#include <zlib.h>

#if !defined(_WIN32) || defined(__MSYS__)
#include <mbedtls/ssl.h>
#endif

#include <nghttp2/nghttp2.h>

#if !defined(_WIN32) && !defined(__MSYS__)
#include <ares.h>
#endif

#include <libpsl.h>
#include <curl/curl.h>
#include <cpr/cpr.h>

auto main() -> int {
  return 0;
}
