#pragma once
#define _WIN32_WINNT 0x0A00
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>

#include <string_view>
#include <cstdint>
#include <unordered_set>
#include <memory>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class Session;
class MessageHandler;

class TcpServer : public std::enable_shared_from_this<TcpServer>
{
public:
	TcpServer(asio::io_context& io_context, std::string_view address, uint16_t port, std::shared_ptr<MessageHandler> msgHandler);
	void Accept();
	void Leave(const std::shared_ptr<Session>& client_session);
	void Stop();
private:
	void Join(const std::shared_ptr<Session>& client_session);
private:
	tcp::acceptor acceptor_;
	std::unordered_set<std::shared_ptr<Session>> sessions_;
	std::shared_ptr<MessageHandler> msgHandler_;
};
