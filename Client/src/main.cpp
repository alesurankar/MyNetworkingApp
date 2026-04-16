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

    App app(running);

    client->SetMessageHandler(
        [&](const std::string& msg) {
            app.OnInput(msg);
        });

    app.SetOutputHandler(
        [&](const std::string& msg) {
            client->Send(msg);
        });

    client->Connect();

    while (running.load()) {
        io.run_one();
        app.Run();
    }

    client->Shutdown();

    return 0;
}