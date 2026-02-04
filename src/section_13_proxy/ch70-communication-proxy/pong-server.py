#!/usr/bin/env python3
"""
Ping-pong server for the Communication Proxy (ch70) C++ client.
GET /api/pingpong/<message> -> response body: "<message> pong"
"""

from http.server import HTTPServer, BaseHTTPRequestHandler
from urllib.parse import unquote

PORT = 8080
API_PREFIX = "/api/pingpong/"


class PingPongHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if not self.path.startswith(API_PREFIX):
            self.send_error(404, "Not Found")
            return

        # /api/pingpong/ping -> message = "ping"
        message = unquote(self.path[len(API_PREFIX) :].strip("/") or "ping")
        body = f"{message} remote pong"

        self.send_response(200)
        self.send_header("Content-Type", "text/plain; charset=utf-8")
        self.send_header("Content-Length", str(len(body.encode("utf-8"))))
        self.end_headers()
        self.wfile.write(body.encode("utf-8"))

    def log_message(self, format, *args):
        print(f"[{self.log_date_time_string()}] {args[0]}")


def main():
    server = HTTPServer(("", PORT), PingPongHandler)
    print(f"Ping-pong server on http://localhost:{PORT}")
    print(f"  GET {API_PREFIX}<message> -> \"<message> remote pong\"")
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nShutting down")
        server.shutdown()


if __name__ == "__main__":
    main()