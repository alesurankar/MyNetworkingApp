#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/streambuf.hpp>

#include <string_view>
#include <cstdint>
#include <unordered_set>
#include <memory>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class Session;

class TcpServer : public std::enable_shared_from_this<TcpServer>
{
public:
	TcpServer(asio::io_context& io_context, std::string_view address, uint16_t port);
	void Accept();
	void Leave(const std::shared_ptr<Session>& client_session);
private:
	void Join(const std::shared_ptr<Session>& client_session);
private:
	tcp::acceptor acceptor_;
	std::unordered_set<std::shared_ptr<Session>> sessions_;
};


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