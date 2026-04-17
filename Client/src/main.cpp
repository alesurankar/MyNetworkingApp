#include <include/config.hpp>
#include <app/app.hpp>
#include <networking/tcp_client.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>

#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <atomic>

namespace asio = boost::asio;

int main()
{
	boost::asio::io_context io;
    std::atomic<bool> running{ true };

    auto client = std::make_shared<TcpClient>(io, config::ADDRESS, config::PORT);
    App app;

    client->SetMessageHandler([&](const std::string& msg) {
            app.OnNetworkMessage(msg);
        });

    app.SetSendHandler([&](const std::string& msg) {
            client->Send(msg);
        });

    app.SetShutdownHandler([&]() {
            running.store(false);
            client->Shutdown();
            io.stop();
        });

    client->Connect();

    std::thread inputThread([&]() {
        std::string msg;
        while (running && std::getline(std::cin, msg)) {
            asio::post(io, [&app, msg]() {
                    app.OnUserInput(msg);
                });
        }
        });

    io.run();

    inputThread.join();

    return 0;
}