
## Project Structure

```
Client/
├─ bin/   # Compiled binaries will be placed here
└─ src/
	├─ app/
	│	├─ app.cpp
	│	└─ app.hpp
	│
	├─ core/
	│	├─ message_handler.cpp
	│	└─ message_handler.hpp
	│
	├─ networking/
	│	├─ connection.cpp
	│	├─ connection.hpp
	│	├─ tcp_client.cpp   # Client implementation using Boost.Asio
	│	└─ tcp_client.hpp
	│
	└─ main.cpp     # Entry Point
```