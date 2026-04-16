#pragma once
#define _WIN32_WINNT 0x0A00
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>

#include <string_view>
#include <cstdint>
#include <memory>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class Connection;

class TcpClient : public std::enable_shared_from_this<TcpClient>
{
public:
	TcpClient(asio::io_context& io_context, std::string_view address, uint16_t port);
	void Connect();
	void Shutdown();
private:
	asio::io_context& io_context_;
	tcp::endpoint endpoint_;
	std::shared_ptr<Connection> connection_;
};
