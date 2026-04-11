#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>

#include <string_view>
#include <cstdint>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class TcpServer
{
public:
	TcpServer(asio::io_context& io_context, std::string_view address, uint16_t port);
	~TcpServer();
	void Accept();
private:
	tcp::acceptor acceptor_;
};