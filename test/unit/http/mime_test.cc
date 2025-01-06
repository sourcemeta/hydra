#include <gtest/gtest.h>

#include <sourcemeta/hydra/http.h>

TEST(HTTP_MIME, css_lower) {
  const std::filesystem::path file_path{"path/to/example.css"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path), "text/css");
}

TEST(HTTP_MIME, css_upper) {
  const std::filesystem::path file_path{"path/to/example.CSS"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path), "text/css");
}

TEST(HTTP_MIME, css_mixed) {
  const std::filesystem::path file_path{"path/to/example.cSs"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path), "text/css");
}

TEST(HTTP_MIME, png_lower) {
  const std::filesystem::path file_path{"path/to/example.png"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path), "image/png");
}

TEST(HTTP_MIME, webp_lower) {
  const std::filesystem::path file_path{"path/to/example.webp"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path), "image/webp");
}

TEST(HTTP_MIME, ico_lower) {
  const std::filesystem::path file_path{"path/to/example.ico"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path),
            "image/vnd.microsoft.icon");
}

TEST(HTTP_MIME, svg_lower) {
  const std::filesystem::path file_path{"path/to/example.svg"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path), "image/svg+xml");
}

TEST(HTTP_MIME, webmanifest_lower) {
  const std::filesystem::path file_path{"path/to/example.webmanifest"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path),
            "application/manifest+json");
}

TEST(HTTP_MIME, json_lower) {
  const std::filesystem::path file_path{"path/to/example.json"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path), "application/json");
}

TEST(HTTP_MIME, woff_lower) {
  const std::filesystem::path file_path{"path/to/example.woff"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path), "font/woff");
}

TEST(HTTP_MIME, woff2_lower) {
  const std::filesystem::path file_path{"path/to/example.woff2"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path), "font/woff2");
}

TEST(HTTP_MIME, html_lower) {
  const std::filesystem::path file_path{"path/to/example.html"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path), "text/html");
}

TEST(HTTP_MIME, unknown) {
  const std::filesystem::path file_path{"path/to/example.foobar"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path),
            "application/octet-stream");
}

TEST(HTTP_MIME, none) {
  const std::filesystem::path file_path{"path/to/example"};
  EXPECT_EQ(sourcemeta::hydra::mime_type(file_path),
            "application/octet-stream");
}
