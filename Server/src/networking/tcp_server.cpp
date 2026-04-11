#include "tcp_server.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/system/detail/error_code.hpp>

#include <string_view>
#include <cstdint>
#include <iostream>
#include <utility>
#include <memory>

using error_code = boost::system::error_code;

// Server
TcpServer::TcpServer(asio::io_context& io_context, std::string_view address, uint16_t port)
	:
	acceptor_(io_context, tcp::endpoint(asio::ip::make_address(address), port))
{
}

void TcpServer::Accept()
{
    std::cout << "Server listening on "
        << acceptor_.local_endpoint().address().to_string()
        << ":"
        << acceptor_.local_endpoint().port()
        << "\n";
    acceptor_.async_accept([this](error_code ec, tcp::socket socket) {
        if (!ec) {
            auto session = std::make_unique<Session>(std::move(socket));
            session->Start();
            Join(std::move(session));
        }
        else {
            std::cerr << "Accept failed: " << ec.message() << "\n";
        }
        Accept(); 
        });
}

void TcpServer::Join(std::unique_ptr<Session> client_session)
{
    std::cout << "TcpServer::Join called";
}

void TcpServer::Leave(std::unique_ptr<Session> client_session)
{
}



// Session
Session::Session(tcp::socket socket)
{
    std::cout << "Session Constructor called";
}

void Session::Start()
{
}

void Session::Stop()
{
}
