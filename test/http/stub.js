const http = require('http');

const server = http.createServer((req, res) => {
  // Set the response header to indicate JSON content
  res.setHeader('Content-Type', 'application/json');

  // Define a simple JSON response
  const jsonResponse = {
    message: 'Hello, JSON World!',
    timestamp: new Date().toISOString(),
  };

  // Send the JSON response
  res.end(JSON.stringify(jsonResponse));
});

const PORT = 9999;
server.listen(PORT, () => {
  console.log(`Server is listening on port ${PORT}`);
});
