#include "session.hpp"
#include <networking/tcp_server.hpp>
#include <core/message_handler.hpp>
#include <networking/connection.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>

#include <utility>
#include <memory>


using error_code = boost::system::error_code;

Session::Session(tcp::socket socket, std::weak_ptr<TcpServer> server, std::shared_ptr<MessageHandler> msgHandler)
    :
    server_(server)
{
    connection_ = std::make_shared<Connection>(std::move(socket), msgHandler);
}

void Session::Start()
{
    connection_->Start();
}

void Session::Stop()
{
    connection_->Stop();
}

//void Session::HandleDisconnect(std::shared_ptr<Session> self)
//{
//    std::cerr << "Client disconnected\n";
//
//    error_code ec;
//
//    if (auto server = server_.lock()) {
//        server->Leave(self);
//    }
//}