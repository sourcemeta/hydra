#include <zlib.h>
// mbedTLS is available on Unix platforms and MSYS2 (Windows/MSVC uses Schannel)
#if !defined(_WIN32) || defined(__MSYS__)
#include <mbedtls/ssl.h>
#endif
#include <nghttp2/nghttp2.h>
// CAres is only available on Unix platforms (excluding MSYS2)
#if !defined(_WIN32) && !defined(__MSYS__)
#include <ares.h>
#endif
#include <libpsl.h>
#include <curl/curl.h>
#include <cpr/cpr.h>

auto main() -> int {
  return 0;
}
