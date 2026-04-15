#pragma once
#define _WIN32_WINNT 0x0A00
#include <boost/asio/ip/tcp.hpp>

#include <memory>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class TcpServer;
class MessageChannel;
class Connection;

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket socket, std::weak_ptr<TcpServer> server, std::shared_ptr<MessageChannel> msgChannel);
	void Start();
	void Stop();
private:
	std::weak_ptr<TcpServer> server_;
	std::shared_ptr<Connection> connection_;
};