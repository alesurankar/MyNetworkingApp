#pragma once
#define _WIN32_WINNT 0x0A00
#include <boost/asio/ip/tcp.hpp>

#include <memory>
#include <cstdint>
#include <string>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class TcpServer;
class Connection;

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket socket, std::weak_ptr<TcpServer> server, uint64_t id);
	void Start();
	void Stop();
	uint64_t GetId() const;
	void Send(const std::string& msg);
private:
	uint64_t id_;
	std::weak_ptr<TcpServer> server_;
	std::shared_ptr<Connection> connection_;
};