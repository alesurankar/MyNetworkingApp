#pragma once
#define _WIN32_WINNT 0x0A00
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/steady_timer.hpp>

#include <memory>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class TcpServer;
class MessageHandler;

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket socket, std::weak_ptr<TcpServer> server, std::shared_ptr<MessageHandler> msgHandler);
	void Start();
	void Stop();
private:
	void ReadMessage();
	void CheckAndSend();
	void HandleDisconnect(std::shared_ptr<Session> self);
private:
	tcp::socket client_socket_;
	std::weak_ptr<TcpServer> server_;
	asio::streambuf input_buffer_;
	asio::steady_timer timer_;
	std::shared_ptr<MessageHandler> msgHandler_;
};