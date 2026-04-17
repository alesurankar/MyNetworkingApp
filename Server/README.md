
# Server (Application)

This project is the **server application** of the system.

It is built on an **event-driven architecture** using Boost.Asio.

The server:
- accepts TCP connections asynchronously
- manages client sessions
- processes messages via callbacks (event handlers)
- runs on a single `io_context` event loop

There are no blocking network operations; all I/O is event-based.


## Project Structure

```
Server/
├─ bin/   # Compiled binaries will be placed here
└─ src/
	├─ app/
	│	├─ app.cpp
	│	└─ app.hpp
	│
	├─ networking/
	│	├─ session.cpp
	│	├─ session.hpp
	│	├─ tcp_server.cpp   # Server implementation using Boost.Asio
	│	└─ tcp_server.hpp
	│
	└─ main.cpp     # Entry Point
```