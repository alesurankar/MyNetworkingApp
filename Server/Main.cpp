#include <boost/asio.hpp>
#include <iostream>


int main()
{
    boost::asio::io_context io;
    std::cout << "Boost.Asio works in Server!\n";

    char c;
    std::cin >> c;

    return 0;
}