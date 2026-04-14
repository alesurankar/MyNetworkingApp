
## Project Structure

```
Client/
├─ bin/   # Compiled binaries will be placed here
└─ src/
	├─ app/
	│	├─ app.hpp
	│	└─ app.cpp
	│
	├─ core/
	│	├─ message_handler.cpp
	│	└─ message_handler.hpp
	│
	├─ networking/
	│	├─ tcp_client.hpp   # Client implementation using Boost.Asio
	│	└─ tcp_client.cpp
	│
	└─ main.cpp     # Entry Point
```