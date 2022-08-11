const http = require('http');
const fs = require('fs').promises;
const path = require('path');
const url = require('url');

function mapContentType(extname) {
  const mimeTypes = {
    '.html': 'text/html',
    '.js': 'text/javascript',
    '.css': 'text/css',
    '.txt': 'text/plain',
    '.json': 'application/json',
    '.png': 'image/png',
    '.jpg': 'image/jpg',
    '.gif': 'image/gif',
    '.svg': 'image/svg+xml',
    '.wav': 'audio/wav',
    '.mp4': 'video/mp4',
    '.woff': 'application/font-woff',
    '.ttf': 'application/font-ttf',
    '.eot': 'application/vnd.ms-fontobject',
    '.otf': 'application/font-otf',
    '.wasm': 'application/wasm',
  };
  return mimeTypes[extname] || 'application/octet-stream';
}

function getRandomNumber(max) {
  if (max === null) return Math.random().toFixed(2);
  return (parseInt(max) * Math.random()).toFixed(2);
}

http
  .createServer(async (request, response) => {
    const requestedURL = new URL('https://127.0.0.1' + request.url);
    console.log('request ', request.url);

    if (requestedURL.pathname === '/random') {
      const max = requestedURL.searchParams.get('max');
      response.writeHead(200, { 'Content-Type': 'text/plain' });
      response.end(`Your random number is ${getRandomNumber(max)}`, 'utf-8');
    } else {
      let filePath = '.' + request.url;
      console.log(filePath);
      if (filePath === './') {
        filePath = './index.html';
      }
      const extname = String(path.extname(filePath)).toLowerCase();
      const contentType = mapContentType(extname);
      try {
        response.writeHead(200, { 'Content-Type': contentType });
        response.end(await fs.readFile(filePath), 'utf-8');
      } catch (error) {
        if (error.code === 'ENOENT') {
          response.writeHead(404, { 'Content-Type': 'text/html' });
          response.end(await fs.readFile('./404.html'), 'utf-8');
        } else {
          response.writeHead(500);
          response.end(
            'Sorry, check with the site admin for error ' + error.code
          );
        }
      }
    }
  })
  .listen(8125);

console.log('Server running at http://127.0.0.1:8125/');
