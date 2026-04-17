#include "tcp_server.hpp"
#include <networking/session.hpp>

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
#include <functional>


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
    acceptor_.async_accept(
        [this, self](error_code ec, tcp::socket socket) {
            if (!ec) {
                uint64_t id = nextClientId_++;
                auto session = std::make_shared<Session>(std::move(socket), id);
                sessions_[id] = session;    //Store session under client ID in the map

                session->SetMessageHandler(
                    [self](uint64_t id, const std::string& msg) {
                        self->OnMessage(id, msg);
                    });

                session->SetDisconnectHandler(
                    [this](uint64_t id) {
                        if (auto it = sessions_.find(id); it != sessions_.end()) {
                            it->second->Close();
                            sessions_.erase(it);
                        }
                    });
                session->Open();
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

void TcpServer::Stop()
{
    error_code ec;

    acceptor_.close(ec);
    for (auto& [id, session] : sessions_) {
        session->Close();
    }
    sessions_.clear();
}

void TcpServer::OnMessage(uint64_t id, const std::string& msg)
{
    std::cout << "Client " << id << ": " << msg << "\n";
    if (onMessage_) {
        onMessage_(id, msg);
    }
}

// callbacks
void TcpServer::SetMessageHandler(MessageHandler handler)
{
    onMessage_ = std::move(handler);
}
