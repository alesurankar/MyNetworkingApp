#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>

#include <string_view>
#include <cstdint>
#include <memory>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class TcpClient : public std::enable_shared_from_this<TcpClient>
{
public:
	TcpClient(asio::io_context& io_context, std::string_view addres, uint16_t port);
	void Connect();
private:
	tcp::socket socket_;
	tcp::endpoint endpoint_;
};