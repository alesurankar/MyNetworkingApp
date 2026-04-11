#include "tcp_server.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>

#include <string_view>
#include <cstdint>
#include <iostream>


TcpServer::TcpServer(asio::io_context& io_context, std::string_view address, uint16_t port)
	:
	acceptor_(io_context, tcp::endpoint(asio::ip::make_address(address), port))
{
}

TcpServer::~TcpServer()
{
}

void TcpServer::Accept()
{
    std::cout << "Server listening on "
        << acceptor_.local_endpoint().address().to_string()
        << ":"
        << acceptor_.local_endpoint().port()
        << "\n";
}
