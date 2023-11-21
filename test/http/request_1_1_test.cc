#include <gtest/gtest.h>
#include <sourcemeta/hydra/http.h>

TEST(HTTP_Request_1_1, XXX) {
  sourcemeta::hydra::http::Request request{BASE_URL};
  request.method(sourcemeta::hydra::http::Method::GET);
  sourcemeta::hydra::http::Response response{request.send().get()};
  EXPECT_EQ(response.status(), sourcemeta::hydra::http::Status::OK);
}
