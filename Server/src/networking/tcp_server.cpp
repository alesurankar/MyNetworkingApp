#include "tcp_server.hpp"
#include "Session.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/system/error_code.hpp>

#include <string_view>
#include <cstdint>
#include <iostream>
#include <utility>
#include <memory>
#include <string>


using error_code = boost::system::error_code;

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
            if (ec == asio::error::operation_aborted) {
                return;
            }
            std::cerr << "Accept failed: " << ec.message() << "\n";
        }
        if (acceptor_.is_open()) {
            Accept();
        }
    });
}

void TcpServer::Join(const std::shared_ptr<Session>& client_session)
{
    sessions_.insert(client_session);
    std::cout << "Client connected. Total: " << sessions_.size() << "\n";
}

void TcpServer::Leave(const std::shared_ptr<Session>& client_session)
{
    client_session->Stop();
    sessions_.erase(client_session); 
    std::cout << "Client disconnected. Total: " << sessions_.size() << "\n";
}

void TcpServer::Stop()
{
    error_code ec;

    acceptor_.close(ec);

    for (auto& session : sessions_) {
        session->Stop();
    }

    sessions_.clear();
}
