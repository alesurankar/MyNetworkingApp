#pragma once
#define _WIN32_WINNT 0x0A00
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>

#include <string_view>
#include <cstdint>
#include <memory>
#include <unordered_map>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class Session;

class TcpServer : public std::enable_shared_from_this<TcpServer>
{
public:
	TcpServer(asio::io_context& io_context, std::string_view address, uint16_t port);
	void Accept();
	void Leave(uint64_t id);
	void Stop();
private:
	tcp::acceptor acceptor_;
	uint64_t nextClientId_ = 0;
	std::unordered_map<uint64_t, std::shared_ptr<Session>> sessions_;
};
