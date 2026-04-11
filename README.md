
this is an Boost playground project

installation:
1. download from https://www.boost.org/releases/latest/
2. extract the downloaded file to your libraries folder.
3. C/C++ → General → Additional Include Directories: add: C:\path\to\boost_1_xx_x (this filder must contain the boost/ folder)

building boost:
1. open the x64 Native Tools Command Prompt for VS
2. navigate to the boost folder: cd C:\path\to\boost_1_xx_x
3. run the command: bootstrap.bat vc143
4. Build boost with the required libraries:
	- full build: .\b2 toolset=msvc --build-type=complete
	- minimal build: .\b2 toolset=msvc --with-system --with-filesystem
5. After the build process is complete, the compiled libraries will be located in the stage/lib directory within the boost folder.
6. Linker → General → Additional Library Directories: add: C:\path\to\boost_1_xx_x\stage\lib


## Project Structure

```
MyNetworkingApp/
├── Controller/   # Startup launcher app
├── Common/       # Shared files
├── Server/       # TCP server (Boost.Asio)
├── Client/       # TCP client
```