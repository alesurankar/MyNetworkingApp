#include "tcp_server.hpp"
#include <networking/session.hpp>
#include <include/core/message_channel.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/error.hpp>

#include <string_view>
#include <cstdint>
#include <iostream>
#include <utility>
#include <memory>
#include <string>


using error_code = boost::system::error_code;

TcpServer::TcpServer(asio::io_context& io_context, std::string_view address, uint16_t port, std::shared_ptr<MessageChannel> msgChannel)
	:
	acceptor_(io_context, tcp::endpoint(asio::ip::make_address(address), port)),
    msgChannel_(std::move(msgChannel))
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
    acceptor_.async_accept(
        [this, self](error_code ec, tcp::socket socket) {
            if (!ec) {
                uint64_t id = nextClientId_++;
                auto session = std::make_shared<Session>(std::move(socket), self, msgChannel_, id);
                sessions_[id] = session;    //Store session under client ID in the map
                session->Start();
                session->Send("ID:" + std::to_string(id));
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

void TcpServer::Leave(uint64_t id)
{
    sessions_.erase(id);
    std::cout << "Client disconnected. Total: " << sessions_.size() << "\n";
}

void TcpServer::Stop()
{
    error_code ec;

    acceptor_.close(ec);
    for (auto& [id, session] : sessions_) {
        session->Stop();
    }
    sessions_.clear();
}