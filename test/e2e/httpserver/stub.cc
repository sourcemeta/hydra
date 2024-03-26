#include <sourcemeta/hydra/httpserver.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <cstdlib>   // EXIT_FAILURE
#include <iostream>  // std::cerr
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::runtime_error
#include <string>    // std::stoul

static auto on_echo(const sourcemeta::hydra::http::ServerRequest &request,
                    sourcemeta::hydra::http::ServerResponse &response) -> void {
  if (request.method() == sourcemeta::hydra::http::Method::HEAD) {
    response.status(sourcemeta::hydra::http::Status::OK);
    response.end();
    return;
  }

  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::JSON::make_object()};

  std::ostringstream method;
  method << request.method();
  document.assign("method", sourcemeta::jsontoolkit::JSON{method.str()});
  document.assign("path", sourcemeta::jsontoolkit::JSON{request.path()});

  std::ostringstream result;
  sourcemeta::jsontoolkit::prettify(document, result);
  response.status(sourcemeta::hydra::http::Status::OK);
  response.header("Content-Type", "application/json");
  response.end(result.str());
}

static auto on_throw(const sourcemeta::hydra::http::ServerRequest &,
                     sourcemeta::hydra::http::ServerResponse &) -> void {
  throw std::runtime_error("Crash!");
}

static auto
on_x_foo(const sourcemeta::hydra::http::ServerRequest &request,
         sourcemeta::hydra::http::ServerResponse &response) -> void {
  response.status(sourcemeta::hydra::http::Status::OK);
  if (request.header("x-foo").has_value()) {
    response.header("x-foo", request.header("x-foo").value());
  }

  response.end();
}

static auto
on_query_foo(const sourcemeta::hydra::http::ServerRequest &request,
             sourcemeta::hydra::http::ServerResponse &response) -> void {
  response.status(sourcemeta::hydra::http::Status::OK);
  if (request.query("foo").has_value()) {
    response.header("x-foo", request.query("foo").value());
  }

  response.end();
}

static auto
on_otherwise(const sourcemeta::hydra::http::ServerRequest &,
             sourcemeta::hydra::http::ServerResponse &response) -> void {
  response.status(sourcemeta::hydra::http::Status::NOT_IMPLEMENTED);
  response.end();
}

static auto
on_error(std::exception_ptr error,
         const sourcemeta::hydra::http::ServerRequest &,
         sourcemeta::hydra::http::ServerResponse &response) noexcept -> void {
  response.status(sourcemeta::hydra::http::Status::BAD_REQUEST);
  try {
    std::rethrow_exception(error);
  } catch (const std::exception &exception) {
    response.end(exception.what());
  }
}

auto main(int argc, char *argv[]) -> int {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <port>\n";
    return EXIT_FAILURE;
  }

  sourcemeta::hydra::http::Server server;

  server.route(sourcemeta::hydra::http::Method::GET, "/echo", on_echo);
  server.route(sourcemeta::hydra::http::Method::HEAD, "/echo", on_echo);
  server.route(sourcemeta::hydra::http::Method::POST, "/echo", on_echo);
  server.route(sourcemeta::hydra::http::Method::PUT, "/echo", on_echo);
  server.route(sourcemeta::hydra::http::Method::DELETE, "/echo", on_echo);
  server.route(sourcemeta::hydra::http::Method::CONNECT, "/echo", on_echo);
  server.route(sourcemeta::hydra::http::Method::OPTIONS, "/echo", on_echo);
  server.route(sourcemeta::hydra::http::Method::TRACE, "/echo", on_echo);
  server.route(sourcemeta::hydra::http::Method::PATCH, "/echo", on_echo);
  server.route(sourcemeta::hydra::http::Method::GET, "/throw", on_throw);
  server.route(sourcemeta::hydra::http::Method::GET, "/echo-x-foo", on_x_foo);
  server.route(sourcemeta::hydra::http::Method::GET, "/echo-query-foo",
               on_query_foo);

  server.otherwise(on_otherwise);
  server.error(on_error);

  return server.run(static_cast<std::uint32_t>(std::stoul(argv[1])));
}
