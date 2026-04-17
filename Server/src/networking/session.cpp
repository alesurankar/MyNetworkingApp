#include "session.hpp"
#include <include/networking/connection.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>

#include <iostream>
#include <utility>
#include <memory>
#include <cstdint>
#include <string>


using error_code = boost::system::error_code;

Session::Session(tcp::socket socket, uint64_t id)
    :
    id_(id)
{
    std::cout << "Session created with ID: " << id_ << "\n";
    connection_ = std::make_shared<Connection>(std::move(socket));
}

void Session::Start()
{
    connection_->SetMessageHandler(
        [this](const std::string& msg) {
            if (onMessage_) {
                onMessage_(id_, msg);
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

void Session::SetMessageHandler(MessageHandler handler)
{
    onMessage_ = std::move(handler);
}

void Session::SetDisconnectHandler(DisconnectHandler handler)
{
    onDisconnect_ = std::move(handler);
}
