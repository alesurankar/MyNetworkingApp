#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>

#include <memory>
#include <string>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class TcpServer;
class MessageHandler;

class Session : public std::enable_shared_from_this<Session>
{
public:
	explicit Session(tcp::socket socket, std::weak_ptr<TcpServer> server, std::shared_ptr<MessageHandler> msgHandler);
	void Start();
	void Stop();
private:
	void ReadMessage();
	void WriteMessage(std::shared_ptr<std::string> msg);
	void HandleDisconnect(std::shared_ptr<Session> self);
private:
	tcp::socket client_socket_;
	std::weak_ptr<TcpServer> server_;
	asio::streambuf input_buffer_;
	std::shared_ptr<MessageHandler> msgHandler_;
};