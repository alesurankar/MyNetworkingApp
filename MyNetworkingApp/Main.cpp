#include <boost/process/v1.hpp>
#include <iostream>

namespace bp = boost::process::v1;

int main()
{
    std::cout << "spawn (s)erver or (c)lient? ";
    char c;
    std::cin >> c;

    try {
        if (c == 's') {
            bp::child server("../Server/bin/Debug/Server.exe");
            server.wait();
        }
        else if (c == 'c') {
            bp::child client("../Client/bin/Debug/Client.exe");
            client.wait();
        }
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    return 0;
}