#include "Session.hpp"
#include "tcp_server.hpp"

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


using error_code = boost::system::error_code;

Session::Session(tcp::socket socket, std::weak_ptr<TcpServer> server)
    :
    client_socket_(std::move(socket)),
    server_(server)
{
    std::cout << "Session Constructor called\n";
}

void Session::Start()
{
    ReadMessage();
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

                std::cout << "Received: " << msg << "\n";
                auto response = std::make_shared<std::string>(msg + "\n");

                WriteMessage(response);
                ReadMessage();
            }
            else {
                HandleDisconnect(self);
            }
        });
}

void Session::WriteMessage(std::shared_ptr<std::string> msg)
{
    auto self = shared_from_this();

    asio::async_write(client_socket_, asio::buffer(*msg),
        [this, self, msg](error_code ec, std::size_t) {
            if (ec) {
                std::cerr << "Write failed\n";
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