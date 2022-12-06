const fs = require('fs');
const http = require('http');

const server = http.createServer(function (req, res) {
    if (req.url == '/') {
        fs.readFile('../docs/webpage/index.html', 'utf-8', function(err, data) {
            res.writeHead(200, { 'Content-Type': 'text/html' });
            res.write(data);
            res.end();
        });
        
    } else if (req.url == "/read") {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.write('1;1;1\n2;2;2\n3;3;3');
        res.end();
    
    } else if (req.url == "/download") {
        fs.readFile('../docs/webpage/demo.csv', 'utf-8', function(err, data) {
            res.writeHead(200, { 'Content-Type': 'text/csv' });
            res.write(data);
            res.end();
        });
    
    } else {
        res.writeHead(404, { 'Content-Type': 'text/html' });
        res.end();
    }
});

const port = 8080;
server.listen(port);
console.log(`Webserver started on port ${port}`)