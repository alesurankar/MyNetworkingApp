#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>

#include <memory>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class TcpServer;

class Session : public std::enable_shared_from_this<Session>
{
public:
	explicit Session(tcp::socket socket, std::weak_ptr<TcpServer> server);
	void Start();
	void Stop();
private:
	void ReadMessage();
private:
	tcp::socket client_socket_;
	std::weak_ptr<TcpServer> server_;
	asio::streambuf input_buffer_;
};