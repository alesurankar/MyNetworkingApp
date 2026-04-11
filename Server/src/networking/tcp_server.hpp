#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>

#include <string_view>
#include <cstdint>
#include <unordered_set>
#include <memory>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class Session;

class TcpServer
{
public:
	TcpServer(asio::io_context& io_context, std::string_view address, uint16_t port);
	void Accept();
	void Leave(std::unique_ptr<Session> client_session);
private:
	void Join(std::unique_ptr<Session> client_session);
private:
	tcp::acceptor acceptor_;
	std::unordered_set<std::unique_ptr<Session>> active_session;
};

class Session
{
public:
	Session(tcp::socket socket);
	void Start();
	void Stop();
private:
};