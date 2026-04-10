#include <iostream>
#include <filesystem>


void launch_in_terminal(const std::string& exe)
{
#ifdef _WIN32
    std::string cmd = "start \"\" \"" + exe + "\"";
    std::system(cmd.c_str());
#elif __linux__
    // TODO
#elif __APPLE__
    // TODO
#endif
}

int main()
{
    std::cout << "CWD: " << std::filesystem::current_path() << "\n";
#ifdef _DEBUG
    std::string config = "Debug";
#else
    std::string config = "Release";
#endif
    std::string serverPath = "Server/bin/" + config + "/Server.exe";
    std::string clientPath = "Client/bin/" + config + "/Client.exe";


    bool running = true;
    while (running) {
        std::cout << "(s)erver or (c)lient or (e)xit";
        char c;
        std::cin >> c;

        try {
            if (c == 's') {
                launch_in_terminal(serverPath);
            }
            else if (c == 'c') {
                launch_in_terminal(clientPath);
            }
            else if (c == 'e') {
                running = false;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}