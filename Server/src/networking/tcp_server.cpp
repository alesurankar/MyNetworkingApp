#include "tcp_server.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/impl/address.ipp>

#include <string>
#include <iostream>


TcpServer::TcpServer(asio::io_context& io_context, const std::string& address, short port)
	:
	acceptor_(io_context, tcp::endpoint(asio::ip::make_address(address), port))
{
}

TcpServer::~TcpServer()
{
}

void TcpServer::Accept()
{
	std::cout << "Waiting for client connection...\n";
}
