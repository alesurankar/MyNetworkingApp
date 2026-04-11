#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>

#include <string>
#include <cstdint>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class TcpClient
{
public:
	TcpClient(asio::io_context& io_context, std::string addres, uint16_t port);
	~TcpClient();
	void Connect();
private:
	tcp::socket socket_;
	tcp::endpoint endpoint_;
};