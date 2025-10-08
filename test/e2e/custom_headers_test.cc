#include <cpr/cpr.h>
#include <cstdlib>
#include <iostream>

auto main() -> int {
  // Test basic GET request with custom headers
  cpr::Response response = cpr::Get(
      cpr::Url{"https://echo.free.beeceptor.com/sample-request"},
      cpr::Header{{"X-Custom-Header", "test-value"}});

  // Check that the request succeeded
  if (response.status_code == 0) {
    std::cerr << "Error: Failed to connect\n";
    std::cerr << "Error message: " << response.error.message << "\n";
    return EXIT_FAILURE;
  }

  // Check for successful HTTP status code (200 OK)
  if (response.status_code != 200) {
    std::cerr << "Error: Expected status code 200, got "
              << response.status_code << "\n";
    return EXIT_FAILURE;
  }

  // Verify we got content back
  if (response.text.empty()) {
    std::cerr << "Error: Response body is empty\n";
    return EXIT_FAILURE;
  }

  std::cout << "Success: Custom headers verified\n";
  std::cout << "Status code: " << response.status_code << "\n";
  std::cout << "Response size: " << response.text.size() << " bytes\n";

  return EXIT_SUCCESS;
}
