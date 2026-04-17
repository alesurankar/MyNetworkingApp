
# Client (Application)

This project is the **client application** of the system.

It is built on an **event-driven architecture** using Boost.Asio.

The client:
- connects to the server asynchronously
- handles incoming messages via callbacks
- sends user input via posted events into the io_context
- processes everything through a single event loop

User input is forwarded into the system using `asio::post`, integrating
console input into the event-driven model.


## Project Structure

```
Client/
├─ bin/   # Compiled binaries will be placed here
└─ src/
	├─ app/
	│	├─ app.cpp
	│	└─ app.hpp
	│
	├─ networking/
	│	├─ tcp_client.cpp   # Client implementation using Boost.Asio
	│	└─ tcp_client.hpp
	│
	└─ main.cpp     # Entry Point
```