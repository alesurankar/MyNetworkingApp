#include <boost/process/v1.hpp>
#include <iostream>

namespace bp = boost::process::v1;

int main()
{
    std::cout << "spawn (s)erver or (c)lient? ";
    char c;
    std::cin >> c;

    if (c == 's') {
        bp::child server("./Server.exe");
        server.wait();
    }
    else if (c == 'c') {
        bp::child client("./Client.exe");
        client.wait();
    }
    return 0;
}