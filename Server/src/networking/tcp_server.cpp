#include "tcp_server.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>

#include <string_view>
#include <cstdint>
#include <iostream>
#include <utility>
#include <memory>
#include <istream>
#include <string>


using error_code = boost::system::error_code;

// Server
TcpServer::TcpServer(asio::io_context& io_context, std::string_view address, uint16_t port)
	:
	acceptor_(io_context, tcp::endpoint(asio::ip::make_address(address), port))
{
    std::cout << "Server listening on "
        << acceptor_.local_endpoint().address().to_string()
        << ":"
        << acceptor_.local_endpoint().port()
        << "\n";
}

void TcpServer::Accept()
{
    auto self = shared_from_this();
    acceptor_.async_accept([this, self](error_code ec, tcp::socket socket) {
        if (!ec) {
            auto session = std::make_shared<Session>(std::move(socket), self);
            session->Start();
            Join(session);
        }
        else {
            std::cerr << "Accept failed: " << ec.message() << "\n";
        }
        Accept(); 
        });
}

void TcpServer::Join(const std::shared_ptr<Session>& client_session)
{
    sessions_.insert(client_session);
}

void TcpServer::Leave(const std::shared_ptr<Session>& client_session)
{
    client_session->Stop();
    sessions_.erase(client_session);
}


// Session
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

    if (client_socket_.is_open()) {
        client_socket_.shutdown(tcp::socket::shutdown_both, ec);
        client_socket_.close(ec);
    }
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

                asio::async_write(client_socket_, asio::buffer(*response),
                    [this, self, response](error_code ec, std::size_t) {
                        if (!ec) {
                            std::cout << "Echo sent\n";
                            ReadMessage();
                        }
                    });
            }
            else {
                std::cerr << "Client disconnected\n";
                if (auto server = server_.lock()) {
                    server->Leave(self);
                }
                return;
            }
        });
}