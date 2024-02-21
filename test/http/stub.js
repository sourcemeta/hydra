const zlib = require('zlib');
const http = require('http');
const PORT = parseInt(process.argv[2], 10);

if (!PORT || isNaN(PORT)) {
  console.error(`Invalid port: ${PORT}`);
  process.exit(1);
}

http.createServer((request, response) => {
  for (const [key, value] of Object.entries(request.headers)) {
    response.setHeader(`X-${key}`, value);
  }

  if (request.headers['x-code']) {
    response.statusCode = parseInt(request.headers['x-code'], 10);
  }

  response.setHeader('Content-Type', 'text/plain');
  response.setHeader('Last-Modified', 'Wed, 21 Oct 2015 11:28:00 GMT');

  const responseData = `RECEIVED ${request.method} ${request.url}`;
  const acceptEncoding = request.headers['accept-encoding'];
  if (acceptEncoding && acceptEncoding.includes('gzip')) {
    response.setHeader('Content-Encoding', 'gzip');
    response.end(zlib.gzipSync(responseData));
  } else {
    response.end(responseData);
  }

}).listen(PORT, () => {
  console.log(`Server is listening on port ${PORT}`);
});
