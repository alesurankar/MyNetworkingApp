#include "session.hpp"
#include <networking/tcp_server.hpp>
#include <core/message_handler.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/system/error_code.hpp>

#include <istream>
#include <iostream>
#include <utility>
#include <string>
#include <memory>
#include <chrono>


using error_code = boost::system::error_code;

Session::Session(tcp::socket socket, std::weak_ptr<TcpServer> server, std::shared_ptr<MessageHandler> msgHandler)
    :
    client_socket_(std::move(socket)),
    server_(server),
    msgHandler_(std::move(msgHandler)),
    timer_(client_socket_.get_executor())
{
    std::cout << "Session Constructor called\n";
}

void Session::Start()
{
    auto self = shared_from_this();
    ReadMessage();
    asio::post(client_socket_.get_executor(), [this, self]() {
        CheckAndSend();
        });
}

void Session::Stop()
{
    error_code ec;

    client_socket_.cancel(ec);
    client_socket_.shutdown(tcp::socket::shutdown_both, ec);
    client_socket_.close(ec);
}

void Session::ReadMessage()
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
                msgHandler_->ServerToMSG(msg);
            }
            ReadMessage();
        }
        else {
            HandleDisconnect(self);
        }
        });
}

void Session::CheckAndSend()
{
    auto self = shared_from_this();
    std::string resp = msgHandler_->MSGToServer();

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

void Session::HandleDisconnect(std::shared_ptr<Session> self)
{
    std::cerr << "Client disconnected\n";

    error_code ec;
    client_socket_.close(ec);

    if (auto server = server_.lock()) {
        server->Leave(self);
    }
}