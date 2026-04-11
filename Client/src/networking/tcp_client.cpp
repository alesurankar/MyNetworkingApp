#include "tcp_client.hpp"

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/impl/address.ipp>

#include <string>
#include <cstdint>
#include <iostream>


TcpClient::TcpClient(asio::io_context& io_context, std::string address, uint16_t port)
	:
	socket_(io_context),
	endpoint_(asio::ip::make_address(address), port)
{
}

TcpClient::~TcpClient()
{
}

void TcpClient::Connect()
{
	std::cout << "Client is connecting...\n";
}
