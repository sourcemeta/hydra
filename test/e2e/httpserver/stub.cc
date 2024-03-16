#include <sourcemeta/hydra/httpserver.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <cstdlib>  // EXIT_FAILURE
#include <iostream> // std::cerr
#include <sstream>  // std::ostringstream
#include <string>   // std::stoul

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

  std::ostringstream result;
  sourcemeta::jsontoolkit::prettify(document, result);
  response.status(sourcemeta::hydra::http::Status::OK);
  response.header("Content-Type", "application/json");
  response.end(result.str());
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

  return server.run(static_cast<std::uint32_t>(std::stoul(argv[1])));
}
