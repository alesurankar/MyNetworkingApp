#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>

#include <string>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class TcpServer
{
public:
	TcpServer(asio::io_context& io_context, const std::string& address, short port);
	~TcpServer();
	void Accept();
private:
	tcp::acceptor acceptor_;
};