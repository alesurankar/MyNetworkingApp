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
    auto app = std::make_shared<App>();

    client->SetMessageHandler([app](const std::string& msg) {
            app->OnNetworkMessage(msg);
        });

    app->SetSendHandler([client](const std::string& msg) {
            client->Send(msg);
        });

    app->SetShutdownHandler([client, &io, &running]() {
            client->Shutdown();
            io.stop();
            running.store(false);
        });

    client->Connect();

    std::thread inputThread([app, &io, &running]() {
        std::string msg;
        while (running.load() && std::getline(std::cin, msg)) {
            asio::post(io, [app, msg]() {
                    app->OnUserInput(msg);
                });
        }
        });

    io.run();
    inputThread.join();

    return 0;
}