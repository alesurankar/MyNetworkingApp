
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
	│	├─ connection.cpp
	│	├─ connection.hpp
	│	├─ session.cpp
	│	├─ session.hpp
	│	├─ tcp_server.cpp   # Server implementation using Boost.Asio
	│	└─ tcp_server.hpp
	│
	└─ main.cpp     # Entry Point
```