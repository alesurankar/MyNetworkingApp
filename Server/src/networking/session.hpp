#pragma once
#define _WIN32_WINNT 0x0A00
#include <boost/asio/ip/tcp.hpp>

#include <memory>
#include <cstdint>
#include <string>
#include <functional>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class Connection;

class Session : public std::enable_shared_from_this<Session>
{
public:
	using MessageHandler = std::function<void(uint64_t, std::string)>;
	using DisconnectHandler = std::function<void(uint64_t)>;

	Session(tcp::socket socket, uint64_t id);
	void Open();
	void Close();
	uint64_t GetId() const;
	void Send(const std::string& msg);
	void SetMessageHandler(MessageHandler handler);
	void SetDisconnectHandler(DisconnectHandler handler);
private:
	uint64_t id_;
	std::shared_ptr<Connection> connection_;
	MessageHandler onMessage_;
	DisconnectHandler onDisconnect_;
};