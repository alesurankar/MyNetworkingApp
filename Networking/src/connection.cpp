#include <networking/connection.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/buffer.hpp>

#include <utility>
#include <string>
#include <memory>
#include <istream>


using error_code = boost::system::error_code;

Connection::Connection(tcp::socket socket)
    :
    socket_(std::move(socket))
{}

void Connection::Start()
{
    DoRead();
}

void Connection::Stop()
{
    error_code ec;

    socket_.cancel(ec);
    socket_.shutdown(tcp::socket::shutdown_both, ec);
    socket_.close(ec);
}

void Connection::Send(const std::string& msg)
{
    auto self = shared_from_this();
    auto message = std::make_shared<std::string>(msg + "\n");

    asio::async_write(socket_, asio::buffer(*message),
        [this, self, message](const error_code& ec, std::size_t) {
            if (ec) {
                Stop();
            }
        });
}

void Connection::DoRead()
{
    auto self = shared_from_this();
    asio::async_read_until(socket_, buffer_, '\n',
        [this, self](error_code ec, std::size_t) {
            if (!ec) {
                std::istream is(&buffer_);
                std::string msg;
                std::getline(is, msg);
                DoRead();
            }
            else {
                Stop();
            }
        });
}
