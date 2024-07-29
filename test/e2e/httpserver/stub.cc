#include <sourcemeta/hydra/httpserver.h>
#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <cassert>   // assert
#include <cstdlib>   // EXIT_FAILURE
#include <iostream>  // std::cerr
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::runtime_error
#include <string>    // std::stoul

static auto on_echo(const sourcemeta::hydra::http::ServerLogger &logger,
                    const sourcemeta::hydra::http::ServerRequest &request,
                    sourcemeta::hydra::http::ServerResponse &response) -> void {
  assert(response.status() == sourcemeta::hydra::http::Status::OK);

  if (request.method() == sourcemeta::hydra::http::Method::HEAD) {
    logger << "Omitting body...";
    response.status(sourcemeta::hydra::http::Status::OK);
    assert(response.status() == sourcemeta::hydra::http::Status::OK);
    response.end();
    return;
  }

  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::JSON::make_object()};

  std::ostringstream method;
  method << request.method();
  document.assign("method", sourcemeta::jsontoolkit::JSON{method.str()});
  document.assign("path", sourcemeta::jsontoolkit::JSON{request.path()});

  response.status(sourcemeta::hydra::http::Status::OK);
  assert(response.status() == sourcemeta::hydra::http::Status::OK);
  response.header("Content-Type", "application/json");
  response.end(document);
}

static auto on_throw(const sourcemeta::hydra::http::ServerLogger &,
                     const sourcemeta::hydra::http::ServerRequest &,
                     sourcemeta::hydra::http::ServerResponse &) -> void {
  throw std::runtime_error("Crash!");
}

static auto
on_x_foo(const sourcemeta::hydra::http::ServerLogger &,
         const sourcemeta::hydra::http::ServerRequest &request,
         sourcemeta::hydra::http::ServerResponse &response) -> void {
  response.status(sourcemeta::hydra::http::Status::OK);
  if (request.header("x-foo").has_value()) {
    response.header("x-foo", request.header("x-foo").value());
  }

  response.end();
}

static auto
on_query_foo(const sourcemeta::hydra::http::ServerLogger &,
             const sourcemeta::hydra::http::ServerRequest &request,
             sourcemeta::hydra::http::ServerResponse &response) -> void {
  response.status(sourcemeta::hydra::http::Status::OK);
  if (request.query("foo").has_value()) {
    response.header("x-foo", request.query("foo").value());
  }

  response.end();
}

static auto
on_otherwise(const sourcemeta::hydra::http::ServerLogger &,
             const sourcemeta::hydra::http::ServerRequest &,
             sourcemeta::hydra::http::ServerResponse &response) -> void {
  response.status(sourcemeta::hydra::http::Status::NOT_IMPLEMENTED);
  assert(response.status() == sourcemeta::hydra::http::Status::NOT_IMPLEMENTED);
  response.end();
}

static auto
on_parameters(const sourcemeta::hydra::http::ServerLogger &,
              const sourcemeta::hydra::http::ServerRequest &request,
              sourcemeta::hydra::http::ServerResponse &response) -> void {
  response.status(sourcemeta::hydra::http::Status::OK);
  std::ostringstream result;
  result << request.parameter(0);
  result << ' ';
  result << request.parameter(1);
  result << ' ';
  result << request.parameter(2);
  response.end(result.str());
}

static auto
on_encodings(const sourcemeta::hydra::http::ServerLogger &,
             const sourcemeta::hydra::http::ServerRequest &request,
             sourcemeta::hydra::http::ServerResponse &response) -> void {
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::JSON::make_array()};
  const auto accept_encoding{request.header_list("accept-encoding")};
  if (accept_encoding.has_value()) {
    for (const auto &encoding : accept_encoding.value()) {
      document.push_back(sourcemeta::jsontoolkit::JSON{encoding.first});
    }
  }

  response.status(sourcemeta::hydra::http::Status::OK);
  response.header("Content-Type", "application/json");
  response.end(document);
}

static auto
on_force_gzip(const sourcemeta::hydra::http::ServerLogger &,
              const sourcemeta::hydra::http::ServerRequest &,
              sourcemeta::hydra::http::ServerResponse &response) -> void {
  response.status(sourcemeta::hydra::http::Status::OK);
  response.encoding(sourcemeta::hydra::http::ServerContentEncoding::GZIP);
  response.end("I am compressed");
}

static auto
on_cache_me(const sourcemeta::hydra::http::ServerLogger &,
            const sourcemeta::hydra::http::ServerRequest &request,
            sourcemeta::hydra::http::ServerResponse &response) -> void {
  const auto timestamp{
      sourcemeta::hydra::http::from_gmt("Wed, 21 Oct 2015 11:28:00 GMT")};
  const auto checksum{"711d2f4adab4515e4036c48bf58eb975"};

  if (!request.header_if_modified_since(timestamp) ||
      !request.header_if_none_match(checksum)) {
    response.status(sourcemeta::hydra::http::Status::NOT_MODIFIED);
    response.end();
    return;
  }

  response.status(sourcemeta::hydra::http::Status::OK);
  response.header_last_modified(timestamp);
  response.header_etag(checksum);
  response.end("Cache me!");
}

static auto
on_etag_quoted(const sourcemeta::hydra::http::ServerLogger &,
               const sourcemeta::hydra::http::ServerRequest &request,
               sourcemeta::hydra::http::ServerResponse &response) -> void {
  const auto checksum{"\"711d2f4adab4515e4036c48bf58eb975\""};
  if (!request.header_if_none_match(checksum)) {
    response.status(sourcemeta::hydra::http::Status::NOT_MODIFIED);
    response.end();
    return;
  }

  response.status(sourcemeta::hydra::http::Status::OK);
  response.header_etag(checksum);
  response.end("Cache me!");
}

static auto
on_schema(const sourcemeta::hydra::http::ServerLogger &,
          const sourcemeta::hydra::http::ServerRequest &request,
          sourcemeta::hydra::http::ServerResponse &response) -> void {
  // Purposely not very well formatted
  const auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "string", "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  response.status(sourcemeta::hydra::http::Status::OK);
  response.header("Content-Type", "application/json");
  if (request.method() == sourcemeta::hydra::http::Method::HEAD) {
    response.head(schema, sourcemeta::jsontoolkit::schema_format_compare);
  } else {
    response.end(schema, sourcemeta::jsontoolkit::schema_format_compare);
  }
}

static auto on_text(const sourcemeta::hydra::http::ServerLogger &,
                    const sourcemeta::hydra::http::ServerRequest &request,
                    sourcemeta::hydra::http::ServerResponse &response) -> void {
  const auto content{"Foo Bar"};
  response.status(sourcemeta::hydra::http::Status::OK);
  response.header("Content-Type", "application/json");
  if (request.method() == sourcemeta::hydra::http::Method::HEAD) {
    response.head(content);
  } else {
    response.end(content);
  }
}

static auto
on_static(const sourcemeta::hydra::http::ServerLogger &,
          const sourcemeta::hydra::http::ServerRequest &request,
          sourcemeta::hydra::http::ServerResponse &response) -> void {
  const std::filesystem::path file_path{STATIC_PATH + request.path().substr(7)};
  if (!std::filesystem::exists(file_path)) {
    response.status(sourcemeta::hydra::http::Status::NOT_FOUND);
    response.end();
    return;
  }

  sourcemeta::hydra::http::serve_file(file_path, request, response);
}

static auto
on_error(std::exception_ptr error,
         const sourcemeta::hydra::http::ServerLogger &,
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

  server.route(sourcemeta::hydra::http::Method::GET, "/schema", on_schema);
  server.route(sourcemeta::hydra::http::Method::HEAD, "/schema", on_schema);
  server.route(sourcemeta::hydra::http::Method::GET, "/text", on_text);
  server.route(sourcemeta::hydra::http::Method::HEAD, "/text", on_text);
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
  server.route(sourcemeta::hydra::http::Method::GET,
               "/parameters/:foo/:bar/:baz", on_parameters);
  server.route(sourcemeta::hydra::http::Method::GET, "/encodings",
               on_encodings);
  server.route(sourcemeta::hydra::http::Method::GET, "/force-gzip",
               on_force_gzip);
  server.route(sourcemeta::hydra::http::Method::GET, "/cache-me", on_cache_me);
  server.route(sourcemeta::hydra::http::Method::POST, "/cache-me", on_cache_me);
  server.route(sourcemeta::hydra::http::Method::GET, "/etag-quoted",
               on_etag_quoted);
  server.route(sourcemeta::hydra::http::Method::GET, "/static/*", on_static);
  server.route(sourcemeta::hydra::http::Method::HEAD, "/static/*", on_static);

  server.otherwise(on_otherwise);
  server.error(on_error);

  return server.run(static_cast<std::uint32_t>(std::stoul(argv[1])));
}
