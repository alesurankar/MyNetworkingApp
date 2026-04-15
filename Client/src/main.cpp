#include <include/config.hpp>
#include <app/app.hpp>
#include <networking/tcp_client.hpp>
#include <include/core/message_channel.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/executor_work_guard.hpp>

#include <atomic>
#include <memory>
#include <thread>


int main()
{
    auto msgChannel = std::make_shared<MessageChannel>();
    std::atomic<bool> running{ true };
    App app(running, msgChannel);

	boost::asio::io_context io;
    auto work_guard = boost::asio::make_work_guard(io);

    auto client = std::make_shared<TcpClient>(io, config::ADDRESS, config::PORT, msgChannel);
	client->Connect();

    std::thread io_thread([&io]() {
        io.run();
        });

    while (running.load()) {
        app.Run();
    }

    client->Shutdown();
    work_guard.reset();
	io.stop();

    if (io_thread.joinable()) {
        io_thread.join();
	}

    return 0;
}