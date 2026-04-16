#include <include/config.hpp>
#include <app/app.hpp>
#include <networking/tcp_client.hpp>

#include <boost/asio/io_context.hpp>

#include <atomic>
#include <memory>


int main()
{
    std::atomic<bool> running{ true };

	boost::asio::io_context io;

    auto client = std::make_shared<TcpClient>(
        io, 
        config::ADDRESS, 
        config::PORT
    );
	client->Connect();

    App app(running);
    while (running.load()) {
        io.poll();
        app.Run();
    }

    client->Shutdown();

    return 0;
}