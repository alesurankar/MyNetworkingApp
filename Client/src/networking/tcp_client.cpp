#include "tcp_client.hpp"
#include <core/message_handler.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <string_view>
#include <cstdint>
#include <iostream>
#include <string>
#include <istream>
#include <memory>
#include <chrono>

using error_code = boost::system::error_code;

TcpClient::TcpClient(asio::io_context& io_context, std::string_view address, uint16_t port, std::shared_ptr<MessageHandler> msgHandler)
	:
	socket_(io_context),
	endpoint_(asio::ip::make_address(address), port),
	timer_(io_context)
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
	socket_.async_connect(endpoint_, [this, self](error_code ec) {
		if (!ec) {
			std::cout << "Connected to server!\n";
			ReadMessage();
			CheckAndSend();
		}
		else {
			std::cerr << "Connect failed: " << ec.message() << "\n";
		}
		});
}

void TcpClient::ReadMessage()
{
	auto self = shared_from_this();

	asio::async_read_until(socket_, input_buffer_, '\n',
		[this, self](error_code ec, std::size_t) {
			if (!ec) {
				std::istream is(&input_buffer_);
				std::string msg;
				std::getline(is, msg);

				std::cout << "Server: " << msg << "\n";

				ReadMessage();
			}
			else {
				std::cerr << "Disconnected from server\n";
			}
		});
}

void TcpClient::CheckAndSend()
{
	auto self = shared_from_this();

	if (!write_queue_.empty()) {
		auto msg = std::make_shared<std::string>(write_queue_.front());
		write_queue_.pop_front();

		asio::async_write(socket_, asio::buffer(*msg),
			[this, self, msg](error_code ec, std::size_t) {
				if (!ec) {
					std::cout << "Message sent\n";
					CheckAndSend();
				}
				else {
					std::cerr << "Send failed: " << ec.message() << "\n";
				}
			});
	}
	else {
		timer_.expires_after(std::chrono::milliseconds(10));
		timer_.async_wait([this, self](error_code ec) {
			if (!ec) {
				CheckAndSend();
			}
			});
	}
}

void TcpClient::Shutdown()
{
	error_code ec;

	timer_.cancel();

	if (socket_.is_open()) {
		socket_.shutdown(tcp::socket::shutdown_both, ec);
		socket_.close(ec);
	}
}