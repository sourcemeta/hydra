const http = require('http');
const PORT = 9999;

http.createServer((request, response) => {
  for (const [key, value] of Object.entries(request.headers)) {
    response.setHeader(`X-${key}`, value);
  }

  if (request.headers['x-code']) {
    response.statusCode = parseInt(request.headers['x-code'], 10);
  }

  response.setHeader('Content-Type', 'text/plain');
  response.end(`RECEIVED ${request.method} ${request.url}`);
}).listen(PORT, () => {
  console.log(`Server is listening on port ${PORT}`);
});
