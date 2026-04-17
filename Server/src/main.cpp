#include <include/config.hpp>
#include <app/app.hpp>
#include <networking/tcp_server.hpp>

#include <boost/asio/io_context.hpp>

#include <memory>
#include <string>
#include <cstdint>


int main()
{
    boost::asio::io_context io;

    auto server = std::make_shared<TcpServer>(io, config::ADDRESS, config::PORT);
    App app;

    server->SetMessageHandler([&](uint64_t id, const std::string& msg) {
            app.OnMessage(id, msg);
        });

    app.SetShutdownHandler([&]() {
            server->Stop();
            io.stop();
        });

    server->Accept();
    io.run();

    return 0;
}