# Chapter 70 — Communication Proxy

A small example of the **Communication Proxy** pattern: a local `Pong` and a `RemotePong` that talks to an HTTP server. Both implement the same `Pingable` interface.

## Python server (pong-server.py)

The server answers `GET /api/pingpong/<message>` with the body `"<message> remote pong"`.

**Run from the project root or this directory:**

```bash
python3 pong-server.py
```

It listens on **http://localhost:8080**. Leave it running while you use the C++ client.

## C++ client (communication-proxy)

**Build** (from the project build directory):

```bash
cmake --build . --target communication-proxy
```

**Run:**

- **On the host** (same machine as the server): run the binary as usual; it uses `http://localhost:8080`.
- **Inside Docker**: the container’s `localhost` is not the host. Either run the client on the host, or point the client at the host (e.g. set the server URL to `http://host.docker.internal:8080` if your client supports it, or use `--network host` on Linux).

**Usage:** The program runs three local `Pong` calls, then three `RemotePong` calls. For the remote calls to succeed, the Python server must be running on port 8080.
