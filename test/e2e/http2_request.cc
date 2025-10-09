#include <cpr/cpr.h>
#include <curl/curl.h>
#include <cstdlib>
#include <iostream>

auto main() -> int {
  cpr::Session session{};
  session.SetUrl(cpr::Url{"https://echo.free.beeceptor.com/sample-request"});

  cpr::Response response = session.Get();

  if (response.status_code == 0) {
    std::cerr << "Error: Failed to connect\n";
    std::cerr << "Error message: " << response.error.message << "\n";
    return EXIT_FAILURE;
  }

  if (response.status_code != 200) {
    std::cerr << "Error: Expected status code 200, got " << response.status_code
              << "\n";
    return EXIT_FAILURE;
  }

  CURL *curl_handle = session.GetCurlHolder()->handle;
  if (curl_handle == nullptr) {
    std::cerr << "Error: Could not get CURL handle\n";
    return EXIT_FAILURE;
  }

  long http_version = 0;
  CURLcode result =
      curl_easy_getinfo(curl_handle, CURLINFO_HTTP_VERSION, &http_version);
  if (result != CURLE_OK) {
    std::cerr << "Error: Failed to get HTTP version info\n";
    return EXIT_FAILURE;
  }

  std::cout << "HTTP version code: " << http_version << "\n";
  if (http_version == CURL_HTTP_VERSION_2_0 ||
      http_version == CURL_HTTP_VERSION_2) {
    std::cout << "Success: HTTP/2 was used\n";
  } else if (http_version == CURL_HTTP_VERSION_1_1) {
    std::cout << "Warning: HTTP/1.1 was used (server may not support HTTP/2)\n";
    return EXIT_FAILURE;
  } else {
    std::cerr << "Unexpected HTTP version: " << http_version << "\n";
    return EXIT_FAILURE;
  }

  std::cout << "Status code: " << response.status_code << "\n";
  std::cout << "Response size: " << response.text.size() << " bytes\n";

  return EXIT_SUCCESS;
}
