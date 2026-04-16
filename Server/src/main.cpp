#include <include/config.hpp>
#include <app/app.hpp>
#include <networking/tcp_server.hpp>

#include <boost/asio/io_context.hpp>

#include <atomic>
#include <memory>


int main()
{
    std::atomic<bool> running{ true };

    boost::asio::io_context io;

    auto server = std::make_shared<TcpServer>(
        io,
        config::ADDRESS,
        config::PORT
    );
    server->Accept();

    App app(running);
    while (running.load())
    {
        io.poll();
        app.Run();
    }

    server->Stop();

    return 0;
}