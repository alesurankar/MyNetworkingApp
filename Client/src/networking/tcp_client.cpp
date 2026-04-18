#include "tcp_client.hpp"
#include <include/networking/connection.hpp>

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

TcpClient::TcpClient(asio::io_context& io_context, std::string_view address, uint16_t port)
	:
	io_context_(io_context),
	endpoint_(asio::ip::make_address(address), port)
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
				connection_ = std::make_shared<Connection>(std::move(*socket));

				connection_->SetMessageHandler(
					[self = shared_from_this()](const std::string& msg) {
						self->HandleIncomingMessage(msg);
					});
				connection_->Open();
			}
			else {
				std::cerr << "Connect failed: " << ec.message() << "\n";
			}
		});
}

void TcpClient::Shutdown()
{
	if (connection_) {
		std::cout << "Stopping connection\n";
		connection_->Close();
	}
}

void TcpClient::Send(const std::string& msg)
{
	if (connection_) {
		connection_->Send(msg);
	}
}

void TcpClient::HandleIncomingMessage(const std::string& msg)
{
	if (msg.starts_with("ID:")) {
		id_ = std::stoull(msg.substr(3));
		std::cout << "Assigned client ID: " << id_ << "\n";
		return;
	}

	if (onMessage_) {
		onMessage_(msg);
	}
}

//Callbacks
void TcpClient::SetMessageHandler(MessageHandler handler)
{
	onMessage_ = std::move(handler);
}
