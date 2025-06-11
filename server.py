import http.server
import os
import socketserver

class RequestHandler(http.server.SimpleHTTPRequestHandler):

    def do_GET(self):
        # update header
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        return http.server.SimpleHTTPRequestHandler.do_GET(self)


    def do_POST(self):
        self.send_response(200)


# start server
server = http.server.HTTPServer(("127.0.0.1", 9999), RequestHandler)
print("Server running")
try:
	server.serve_forever()
except KeyboardInterrupt:
	server.server_close()
	print("Server Closed")	