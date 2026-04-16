#include "session.hpp"
#include <networking/tcp_server.hpp>
#include <include/networking/connection.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>

#include <iostream>
#include <utility>
#include <memory>
#include <cstdint>


using error_code = boost::system::error_code;

Session::Session(tcp::socket socket, std::weak_ptr<TcpServer> server, uint64_t id)
    :
    server_(server),
    id_(id)
{
    std::cout << "Session created with ID: " << id_ << "\n";
    connection_ = std::make_shared<Connection>(std::move(socket));
}

void Session::Start()
{
    connection_->SetMessageHandler(
        [this](const std::string& msg) {
            if (auto server = server_.lock()) {
                server->OnMessage(id_, msg);
            }
        });

    connection_->Start();
}

void Session::Stop()
{
    connection_->Stop();
}

uint64_t Session::GetId() const
{
    return id_;
}

void Session::Send(const std::string& msg)
{
    connection_->Send(msg);
}