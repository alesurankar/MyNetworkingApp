#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/steady_timer.hpp>

#include <string_view>
#include <cstdint>
#include <memory>
#include <string>
#include <deque>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class TcpClient : public std::enable_shared_from_this<TcpClient>
{
public:
	TcpClient(asio::io_context& io_context, std::string_view address, uint16_t port);
	void Connect();
	void Send(const std::string& message);
private:
	void CheckAndSend();
	void ReadMessage();
private:
	tcp::socket socket_;
	tcp::endpoint endpoint_;
	asio::streambuf input_buffer_;
	std::deque<std::string> write_queue_;
	asio::steady_timer timer_;
};
