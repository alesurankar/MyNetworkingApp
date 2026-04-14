#include "connection.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/post.hpp>

#include <utility>
#include <string>
#include <memory>


using error_code = boost::system::error_code;

Connection::Connection(tcp::socket socket, std::shared_ptr<MessageHandler> msgHandler)
	:
	socket_(std::move(socket)),
    timer_(socket_.get_executor())
{

}

void Connection::Start()
{
    DoRead();

    auto self = shared_from_this();
    asio::post(socket_.get_executor(),
        [this, self]()
        {
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

void Connection::Send(const std::string& msg)
{

}

void Connection::DoRead()
{

}

void Connection::DoWrite()
{

}


void Connection::ReadMessage()
{
    auto self = shared_from_this();
    asio::async_read_until(client_socket_, input_buffer_, '\n',
        [this, self](error_code ec, std::size_t) {
            if (!ec) {
                std::istream is(&input_buffer_);
                std::string msg;
                std::getline(is, msg);

                std::cout << "\nStep1. '" << msg << "' received from client... TcpSession::ReadMessage (networking thread)\n";
                if (!msg.empty()) {
                    msgHandler_->NetToHandler(msg);
                }
                ReadMessage();
            }
            else {
                HandleDisconnect(self);
            }
        });
}

void Connection::CheckAndSend()
{
    auto self = shared_from_this();
    std::string resp = msgHandler_->HandlerToNet();

    if (resp.empty()) {
        timer_.expires_after(std::chrono::milliseconds(10));
        timer_.async_wait([this, self](error_code ec) {
            if (!ec) {
                CheckAndSend();
            }
            });
        return;
    }

    resp.push_back('\n');
    auto msg = std::make_shared<std::string>(std::move(resp));

    asio::async_write(client_socket_, boost::asio::buffer(*msg),
        [this, self, msg](const boost::system::error_code& ec, std::size_t) {
            if (!ec) {
                std::cout << "Step10.'" << *msg << "' sent to client... Session::CheckAndSend\n";
                CheckAndSend();
            }
            else {
                HandleDisconnect(self);
            }
        });
}
