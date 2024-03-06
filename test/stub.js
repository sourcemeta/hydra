const zlib = require('zlib');
const http = require('http');
const PORT = parseInt(process.argv[2], 10);

if (!PORT || isNaN(PORT)) {
  console.error(`Invalid port: ${PORT}`);
  process.exit(1);
}

let increment = 0;

http.createServer((request, response) => {
  if (request.url === '/bucket/1.json') {
    if (!request.headers.authorization ||
      !request.headers.host ||
      !request.headers['x-amz-date']) {
      response.statusCode = 401;
      return response.end();
    }

    if (request.headers['if-none-match'] === '"1111111111"') {
      response.statusCode = 304;
      return response.end();
    }

    response.statusCode = 200;
    response.setHeader('Content-Type', 'application/json');
    response.setHeader('Last-Modified', 'Wed, 21 Oct 2015 11:28:00 GMT');
    response.setHeader('ETag', '"1111111111"');
    return response.end(JSON.stringify({ foo: 1 }));
  }

  if (request.url === '/bucket/incremental.json') {
    if (!request.headers.authorization ||
      !request.headers.host ||
      !request.headers['x-amz-date']) {
      response.statusCode = 401;
      return response.end();
    }

    const etag = `"${String(increment).repeat(10)}"`;
    if (request.headers['if-none-match'] === etag) {
      response.statusCode = 304;
      return response.end();
    }

    response.statusCode = 200;
    response.setHeader('Content-Type', 'application/json');
    response.setHeader('Last-Modified', 'Wed, 21 Oct 2015 11:28:00 GMT');
    response.setHeader('ETag', etag);
    response.end(JSON.stringify({ value: increment }));
    increment += 1;
    return;
  }

  for (const [key, value] of Object.entries(request.headers)) {
    response.setHeader(`X-${key}`, value);
  }

  if (request.headers['x-code']) {
    response.statusCode = parseInt(request.headers['x-code'], 10);
  }

  response.setHeader('Content-Type', 'text/plain');
  response.setHeader('Last-Modified', 'Wed, 21 Oct 2015 11:28:00 GMT');

  let requestBody = [];
  request.on('data', (chunk) => {
    requestBody.push(chunk);
  });

  request.on('end', () => {
    const responseData = requestBody.length === 0
      ? `RECEIVED ${request.method} ${request.url}`
      : Buffer.concat(requestBody).toString();
    const acceptEncoding = request.headers['accept-encoding'];
    if (acceptEncoding && acceptEncoding.includes('gzip')) {
      response.setHeader('Content-Encoding', 'gzip');
      response.end(zlib.gzipSync(responseData));
    } else {
      response.end(responseData);
    }
  });
}).listen(PORT, () => {
  console.log(`Server is listening on port ${PORT}`);
});
