#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>

#include <memory>
#include <string>
#include <functional>
#include <deque>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    using MessageHandler = std::function<void(const std::string&)>;
    using DisconnectHandler = std::function<void()>;

    Connection(tcp::socket socket);
    void Open();
    void Close();
    void Send(const std::string& msg);
    void SetMessageHandler(MessageHandler handler);
    void SetDisconnectHandler(DisconnectHandler handler);
private:
    void DoRead();
	void DoWrite();
private:
    tcp::socket socket_;
    asio::streambuf buffer_;
    MessageHandler onMessage_;
    DisconnectHandler onDisconnect_;
    std::deque<std::string> writeQueue_;
};