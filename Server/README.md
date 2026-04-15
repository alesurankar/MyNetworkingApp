
# Server (Application)

This project is the **server application** of the system.

It accepts TCP connections from clients, manages sessions,
and processes messages using the shared Networking and Common layers.


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