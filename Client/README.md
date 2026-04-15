
# Client (Application)

This project is the **client application** of the system.

It connects to the Server over TCP using the Networking library
and processes user input and server responses through the App layer.


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