#include "connection.hpp"
#include <core/message_handler.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/post.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/buffer.hpp>

#include <utility>
#include <string>
#include <memory>
#include <istream>
#include <chrono>


using error_code = boost::system::error_code;

Connection::Connection(tcp::socket socket, std::shared_ptr<MessageHandler> msgHandler)
    :
    socket_(std::move(socket)),
    timer_(socket_.get_executor()),
    msgHandler_(std::move(msgHandler))
{}

void Connection::Start()
{
    DoRead();

    auto self = shared_from_this();
    asio::post(socket_.get_executor(),
        [this, self]() {
            DoWrite();
        });
}

void Connection::Stop()
{
    error_code ec;

    socket_.cancel(ec);
    socket_.shutdown(tcp::socket::shutdown_both, ec);
    socket_.close(ec);
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

                if (!msg.empty()) {
                    msgHandler_->NetToHandler(msg);
                }
                DoRead();
            }
            else {
                Stop();
            }
        });
}

void Connection::DoWrite()
{
    auto self = shared_from_this();
    std::string resp = msgHandler_->HandlerToNet();

    if (resp.empty()) {
        timer_.expires_after(std::chrono::milliseconds(10));
        timer_.async_wait(
            [this, self](error_code ec) {
                if (!ec) {
                    DoWrite();
                }
            });
        return;
    }

    resp.push_back('\n');
    auto msg = std::make_shared<std::string>(std::move(resp));

    asio::async_write(socket_, asio::buffer(*msg),
        [this, self, msg](const error_code& ec, std::size_t) {
            if (!ec) {
                DoWrite();
            }
            else {
                Stop();
            }
        });
}
