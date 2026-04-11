#include "tcp_client.hpp"

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>

#include <string_view>
#include <cstdint>
#include <iostream>


TcpClient::TcpClient(asio::io_context& io_context, std::string_view address, uint16_t port)
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
	std::cout << "Client is connecting to "
		<< endpoint_.address().to_string()
		<< ":"
		<< endpoint_.port()
		<< "\n";
}
