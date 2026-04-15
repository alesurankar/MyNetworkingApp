#include "tcp_client.hpp"
#include <include/core/message_channel.hpp>
#include <networking/connection.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <string_view>
#include <cstdint>
#include <iostream>
#include <string>
#include <memory>
#include <utility>


using error_code = boost::system::error_code;

TcpClient::TcpClient(asio::io_context& io_context, std::string_view address, uint16_t port, std::shared_ptr<MessageChannel> msgChannel)
	:
	io_context_(io_context),
	endpoint_(asio::ip::make_address(address), port),
	msgChannel_(std::move(msgChannel))
{
	std::cout << "Client is connecting to "
		<< endpoint_.address().to_string()
		<< ":"
		<< endpoint_.port()
		<< "\n";
}

void TcpClient::Connect()
{
	auto self = shared_from_this();
	auto socket = std::make_shared<tcp::socket>(io_context_);

	socket->async_connect(endpoint_, 
		[this, self, socket](error_code ec) {
			if (!ec) {
				std::cout << "Connected to server!\n";
				connection_ = std::make_shared<Connection>(std::move(*socket), msgChannel_);
				connection_->Start();
			}
			else {
				std::cerr << "Connect failed: " << ec.message() << "\n";
			}
		});
}

void TcpClient::Shutdown()
{
	if (connection_) {
		std::cout << "Stoping connection\n";
		connection_->Stop();
	}
}