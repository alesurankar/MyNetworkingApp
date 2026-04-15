#include "session.hpp"
#include <networking/tcp_server.hpp>
#include <include/core/message_channel.hpp>
#include <include/networking/connection.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>

#include <utility>
#include <memory>


using error_code = boost::system::error_code;

Session::Session(tcp::socket socket, std::weak_ptr<TcpServer> server, std::shared_ptr<MessageChannel> msgChannel)
    :
    server_(server)
{
    connection_ = std::make_shared<Connection>(std::move(socket), msgChannel);
}

void Session::Start()
{
    connection_->Start();
}

void Session::Stop()
{
    connection_->Stop();
}
