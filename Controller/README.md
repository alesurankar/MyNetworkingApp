# MyNetworkingApp

## Overview

This is a small controller application used to launch a TCP server and client from a single executable.

It simplifies testing by allowing you to quickly spawn either:

* a server instance
* a client instance

## Features

* Launch server or client from a menu
* Automatically selects Debug/Release build
* Cross-platform structure (Windows implemented, Linux/macOS planned)


## Build

Make sure all projects are built first (Server, Client, Controller).

Example (depending on your setup):

* Build in Debug or Release mode
* Ensure binaries exist:

  * `Server/bin/Debug/Server.exe`
  * `Client/bin/Debug/Client.exe`

## Usage

Run the controller,
Then choose:

```
(s)erver  → launches server
(c)lient  → launches client
(e)xit    → quits application
```

## Notes

* Currently Windows-only terminal launching is implemented.
* Linux and macOS support is planned.

## Future Improvements

* Add Linux/macOS terminal launching
* Improve error handling (missing binaries, paths)
* Allow multiple clients
* Configurable paths
