#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <sourcemeta/hydra/httpclient.h>

#include "http_base_url.h"

TEST(HTTP_Stream_1_1, invalid_url) {
  sourcemeta::hydra::http::ClientStream request{"foobarbaz"};
  EXPECT_THROW(request.send().wait(), sourcemeta::hydra::http::Error);
}

TEST(HTTP_Stream_1_1, retrieve_url) {
  sourcemeta::hydra::http::ClientStream request{"https://www.example.com"};
  EXPECT_EQ(request.url(), "https://www.example.com");
}

TEST(HTTP_Stream_1_1, retrieve_method) {
  sourcemeta::hydra::http::ClientStream request{"https://www.example.com"};
  request.method(sourcemeta::hydra::http::Method::HEAD);
  EXPECT_EQ(request.method(), sourcemeta::hydra::http::Method::HEAD);
}

TEST(HTTP_Stream_1_1, method_get_by_default) {
  sourcemeta::hydra::http::ClientStream request{"https://www.example.com"};
  EXPECT_EQ(request.method(), sourcemeta::hydra::http::Method::GET);
}

TEST(HTTP_Stream_1_1, no_callbacks_get) {
  sourcemeta::hydra::http::ClientStream request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  const auto status{request.send().get()};
  EXPECT_EQ(status, sourcemeta::hydra::http::Status::OK);
}

TEST(HTTP_Stream_1_1, no_callbacks_head) {
  sourcemeta::hydra::http::ClientStream request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::HEAD);
  const auto status{request.send().get()};
  EXPECT_EQ(status, sourcemeta::hydra::http::Status::OK);
}

TEST(HTTP_Stream_1_1, get_empty) {
  sourcemeta::hydra::http::ClientStream request{std::string{HTTP_BASE_URL()} +
                                                "/empty"};
  request.method(sourcemeta::hydra::http::Method::GET);

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
  EXPECT_EQ(status, sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(statuses.empty());
  EXPECT_TRUE(std::all_of(statuses.cbegin(), statuses.cend(), [](auto value) {
    return value == sourcemeta::hydra::http::Status::OK;
  }));

  // Headers
  EXPECT_TRUE(headers.contains("content-length"));
  EXPECT_EQ(headers.at("content-length"), "0");

  // Body
  EXPECT_EQ(body.str(), "");
}

TEST(HTTP_Stream_1_1, unsigned_long_header) {
  sourcemeta::hydra::http::ClientStream request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);
  const unsigned long number{11};
  request.header("x-foo", number);

  std::map<std::string, std::string> headers;
  request.on_header([&headers](const sourcemeta::hydra::http::Status,
                               std::string_view key,
                               std::string_view value) noexcept {
    headers.emplace(key, value);
  });

  const auto status{request.send().get()};

  // Status
  EXPECT_EQ(status, sourcemeta::hydra::http::Status::OK);

  // Headers
  EXPECT_TRUE(headers.contains("x-x-foo"));
  EXPECT_EQ(headers.at("x-x-foo"), std::to_string(number));
}

TEST(HTTP_Stream_1_1, post_empty) {
  sourcemeta::hydra::http::ClientStream request{std::string{HTTP_BASE_URL()} +
                                                "/empty"};
  request.method(sourcemeta::hydra::http::Method::POST);

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
  EXPECT_EQ(status, sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(statuses.empty());
  EXPECT_TRUE(std::all_of(statuses.cbegin(), statuses.cend(), [](auto value) {
    return value == sourcemeta::hydra::http::Status::OK;
  }));

  // Headers
  EXPECT_TRUE(headers.contains("content-length"));
  EXPECT_EQ(headers.at("content-length"), "0");

  // Body
  EXPECT_EQ(body.str(), "");
}

TEST(HTTP_Stream_1_1, get_root_foo_bar) {
  sourcemeta::hydra::http::ClientStream request{std::string{HTTP_BASE_URL()} +
                                                "/foo/bar"};
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

TEST(HTTP_Stream_1_1, on_body_exception) {
  sourcemeta::hydra::http::ClientStream request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::POST);

  request.on_body([](const std::size_t) -> std::vector<std::uint8_t> {
    throw std::runtime_error("Error!");
  });

  EXPECT_THROW(request.send().get(), sourcemeta::hydra::http::Error);
}

TEST(HTTP_Stream_1_1, post_root_hello_world) {
  sourcemeta::hydra::http::ClientStream request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::POST);

  std::vector<sourcemeta::hydra::http::Status> statuses;
  std::istringstream request_body{"hello world"};
  std::ostringstream response_body;

  request.on_data([&statuses, &response_body](
                      const sourcemeta::hydra::http::Status status,
                      std::span<const std::uint8_t> buffer) noexcept {
    statuses.push_back(status);
    for (const auto byte : buffer) {
      response_body << static_cast<char>(byte);
    }
  });

  request.on_header([&statuses](const sourcemeta::hydra::http::Status status,
                                std::string_view, std::string_view) noexcept {
    statuses.push_back(status);
  });

  request.on_body([&request_body](const std::size_t bytes) {
    std::vector<std::uint8_t> result;
    while (result.size() < bytes && request_body.peek() != EOF) {
      result.push_back(static_cast<std::uint8_t>(request_body.get()));
    }

    return result;
  });

  const auto status{request.send().get()};

  // Status
  EXPECT_EQ(status, sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(statuses.empty());
  EXPECT_TRUE(std::all_of(statuses.cbegin(), statuses.cend(), [](auto value) {
    return value == sourcemeta::hydra::http::Status::OK;
  }));

  // Body
  EXPECT_EQ(response_body.str(), "RECEIVED POST hello world");
}

TEST(HTTP_Stream_1_1, put_root_hello_world) {
  sourcemeta::hydra::http::ClientStream request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::PUT);

  std::vector<sourcemeta::hydra::http::Status> statuses;
  std::istringstream request_body{"hello world"};
  std::ostringstream response_body;

  request.on_data([&statuses, &response_body](
                      const sourcemeta::hydra::http::Status status,
                      std::span<const std::uint8_t> buffer) noexcept {
    statuses.push_back(status);
    for (const auto byte : buffer) {
      response_body << static_cast<char>(byte);
    }
  });

  request.on_header([&statuses](const sourcemeta::hydra::http::Status status,
                                std::string_view, std::string_view) noexcept {
    statuses.push_back(status);
  });

  request.on_body([&request_body](const std::size_t bytes) {
    std::vector<std::uint8_t> result;
    while (result.size() < bytes && request_body.peek() != EOF) {
      result.push_back(static_cast<std::uint8_t>(request_body.get()));
    }

    return result;
  });

  const auto status{request.send().get()};

  // Status
  EXPECT_EQ(status, sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(statuses.empty());
  EXPECT_TRUE(std::all_of(statuses.cbegin(), statuses.cend(), [](auto value) {
    return value == sourcemeta::hydra::http::Status::OK;
  }));

  // Body
  EXPECT_EQ(response_body.str(), "RECEIVED PUT hello world");
}

TEST(HTTP_Stream_1_1, get_root_hello_world) {
  sourcemeta::hydra::http::ClientStream request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::GET);

  std::vector<sourcemeta::hydra::http::Status> statuses;
  std::istringstream request_body{"hello world"};
  std::ostringstream response_body;

  request.on_data([&statuses, &response_body](
                      const sourcemeta::hydra::http::Status status,
                      std::span<const std::uint8_t> buffer) noexcept {
    statuses.push_back(status);
    for (const auto byte : buffer) {
      response_body << static_cast<char>(byte);
    }
  });

  request.on_header([&statuses](const sourcemeta::hydra::http::Status status,
                                std::string_view, std::string_view) noexcept {
    statuses.push_back(status);
  });

  request.on_body([&request_body](const std::size_t bytes) {
    std::vector<std::uint8_t> result;
    while (result.size() < bytes && request_body.peek() != EOF) {
      result.push_back(static_cast<std::uint8_t>(request_body.get()));
    }

    return result;
  });

  const auto status{request.send().get()};

  // Status
  EXPECT_EQ(status, sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(statuses.empty());
  EXPECT_TRUE(std::all_of(statuses.cbegin(), statuses.cend(), [](auto value) {
    return value == sourcemeta::hydra::http::Status::OK;
  }));

  // Body
  EXPECT_EQ(response_body.str(), "RECEIVED GET hello world");
}

TEST(HTTP_Stream_1_1, post_root_empty_body) {
  sourcemeta::hydra::http::ClientStream request{HTTP_BASE_URL()};
  request.method(sourcemeta::hydra::http::Method::POST);

  std::vector<sourcemeta::hydra::http::Status> statuses;
  std::ostringstream response_body;

  request.on_data([&statuses, &response_body](
                      const sourcemeta::hydra::http::Status status,
                      std::span<const std::uint8_t> buffer) noexcept {
    statuses.push_back(status);
    for (const auto byte : buffer) {
      response_body << static_cast<char>(byte);
    }
  });

  request.on_header([&statuses](const sourcemeta::hydra::http::Status status,
                                std::string_view, std::string_view) noexcept {
    statuses.push_back(status);
  });

  request.on_body(
      [](const std::size_t) -> std::vector<std::uint8_t> { return {}; });

  const auto status{request.send().get()};

  // Status
  EXPECT_EQ(status, sourcemeta::hydra::http::Status::OK);
  EXPECT_FALSE(statuses.empty());
  EXPECT_TRUE(std::all_of(statuses.cbegin(), statuses.cend(), [](auto value) {
    return value == sourcemeta::hydra::http::Status::OK;
  }));

  // Body
  EXPECT_EQ(response_body.str(), "RECEIVED POST /");
}
