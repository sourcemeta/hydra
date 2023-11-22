#include <algorithm>
#include <map>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>
#include <sourcemeta/hydra/http.h>

TEST(HTTP_Stream_1_1, invalid_url) {
  sourcemeta::hydra::http::Stream request{"foobarbaz"};
  EXPECT_THROW(request.send().wait(), sourcemeta::hydra::http::Error);
}

TEST(HTTP_Stream_1_1, no_callbacks_get) {
  sourcemeta::hydra::http::Stream request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  const auto status{request.send().get()};
  EXPECT_EQ(status, sourcemeta::hydra::http::Status::OK);
}

TEST(HTTP_Stream_1_1, no_callbacks_head) {
  sourcemeta::hydra::http::Stream request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::HEAD);
  const auto status{request.send().get()};
  EXPECT_EQ(status, sourcemeta::hydra::http::Status::OK);
}

TEST(HTTP_Stream_1_1, get_root_foo_bar) {
  sourcemeta::hydra::http::Stream request{std::string{BASE_URL} + "/foo/bar"};
  request.method(sourcemeta::hydra::http::Method::GET);
  request.header("X-Code", 400);

  std::vector<sourcemeta::hydra::http::Status> statuses;
  std::map<std::string, std::string> headers;
  std::ostringstream body;

  request.on_data(
      [&statuses, &body](const sourcemeta::hydra::http::Status status,
                         std::span<const std::uint8_t> buffer) noexcept {
        statuses.push_back(status);
        for (const auto byte : buffer) {
          body << static_cast<char>(byte);
        }
      });

  request.on_header([&statuses, &headers](
                        const sourcemeta::hydra::http::Status status,
                        std::string_view key, std::string_view value) noexcept {
    statuses.push_back(status);
    headers.emplace(key, value);
  });

  const auto status{request.send().get()};

  // Status
  EXPECT_EQ(status, sourcemeta::hydra::http::Status::BAD_REQUEST);
  EXPECT_FALSE(statuses.empty());
  EXPECT_TRUE(std::all_of(statuses.cbegin(), statuses.cend(), [](auto value) {
    return value == sourcemeta::hydra::http::Status::BAD_REQUEST;
  }));

  // Headers
  EXPECT_TRUE(headers.contains("content-type"));
  EXPECT_EQ(headers.at("content-type"), "text/plain");

  // Body
  EXPECT_EQ(body.str(), "RECEIVED GET /foo/bar");
}
