#pragma once
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/steady_timer.hpp>

#include <memory>
#include <deque>
#include <string>


namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class MessageChannel;

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    Connection(tcp::socket socket, std::shared_ptr<MessageChannel> msgChannel);
    void Start();
    void Stop(); 
    void Send(const std::string& msg);
private:
    void DoRead();
    void DoWrite();
private:
    tcp::socket socket_;
    asio::streambuf buffer_;
    asio::steady_timer timer_;
    std::deque<std::string> writeQueue_;
    std::shared_ptr<MessageChannel> msgChannel_;
};