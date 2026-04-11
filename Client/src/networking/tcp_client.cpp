#include "tcp_client.hpp"

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/system/error_code.hpp>

#include <string_view>
#include <cstdint>
#include <iostream>


using error_code = boost::system::error_code;

TcpClient::TcpClient(asio::io_context& io_context, std::string_view address, uint16_t port)
	:
	socket_(io_context),
	endpoint_(asio::ip::make_address(address), port)
{
}

void TcpClient::Connect()
{
	std::cout << "Client is connecting to "
		<< endpoint_.address().to_string()
		<< ":"
		<< endpoint_.port()
		<< "\n";
	socket_.async_connect(endpoint_, [this](error_code ec) {
		if (!ec) {
			std::cout << "Connected to server!\n";
		}
		else {
			std::cerr << "Connect failed: " << ec.message() << "\n";
		}
		});
}
