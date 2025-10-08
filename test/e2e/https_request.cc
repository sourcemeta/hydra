#include <cpr/cpr.h>
#include <cstdlib>
#include <iostream>
#include <string>

auto main() -> int {
  // Make HTTPS request to example.com
  cpr::Response response = cpr::Get(cpr::Url{"https://example.com"});

  // Check that the request succeeded
  if (response.status_code == 0) {
    std::cerr << "Error: Failed to connect to example.com\n";
    std::cerr << "Error message: " << response.error.message << "\n";
    return EXIT_FAILURE;
  }

  // Check for successful HTTP status code (200 OK)
  if (response.status_code != 200) {
    std::cerr << "Error: Expected status code 200, got " << response.status_code
              << "\n";
    return EXIT_FAILURE;
  }

  // Check that we received some content
  if (response.text.empty()) {
    std::cerr << "Error: Response body is empty\n";
    return EXIT_FAILURE;
  }

  // Check for expected Content-Type header
  auto content_type_iterator = response.header.find("content-type");
  if (content_type_iterator == response.header.end()) {
    std::cerr << "Error: Content-Type header not found\n";
    return EXIT_FAILURE;
  }

  const std::string &content_type = content_type_iterator->second;
  if (content_type.find("text/html") == std::string::npos) {
    std::cerr << "Error: Expected Content-Type to contain 'text/html', got '"
              << content_type << "'\n";
    return EXIT_FAILURE;
  }

  // Check that the response contains expected example.com content
  if (response.text.find("Example Domain") == std::string::npos) {
    std::cerr
        << "Error: Response body does not contain expected 'Example Domain'\n";
    return EXIT_FAILURE;
  }

  std::cout << "Success: HTTPS request to example.com completed successfully\n";
  std::cout << "Status code: " << response.status_code << "\n";
  std::cout << "Content-Type: " << content_type << "\n";
  std::cout << "Response size: " << response.text.size() << " bytes\n";

  return EXIT_SUCCESS;
}
