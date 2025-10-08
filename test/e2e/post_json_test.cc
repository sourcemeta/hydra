#include <cpr/cpr.h>
#include <cstdlib>
#include <iostream>
#include <string>

auto main() -> int {
  // Test POST request with form data
  cpr::Response response =
      cpr::Post(cpr::Url{"https://echo.free.beeceptor.com/post-test"},
                cpr::Payload{{"field1", "value1"}, {"field2", "value2"}});

  // Check that the request succeeded
  if (response.status_code == 0) {
    std::cerr << "Error: Failed to connect\n";
    std::cerr << "Error message: " << response.error.message << "\n";
    return EXIT_FAILURE;
  }

  // Check for successful HTTP status code (200 or 201)
  if (response.status_code != 200 && response.status_code != 201) {
    std::cerr << "Error: Expected status code 200 or 201, got "
              << response.status_code << "\n";
    return EXIT_FAILURE;
  }

  // Verify we got a response back
  if (response.text.empty()) {
    std::cerr << "Error: Response body is empty\n";
    return EXIT_FAILURE;
  }

  std::cout << "Success: POST request verified\n";
  std::cout << "Status code: " << response.status_code << "\n";
  std::cout << "Response size: " << response.text.size() << " bytes\n";

  return EXIT_SUCCESS;
}
