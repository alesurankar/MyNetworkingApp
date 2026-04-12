#include <app/app.hpp>
#include <networking/tcp_server.hpp>
#include <Common/config.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/executor_work_guard.hpp>

#include <atomic>
#include <memory>
#include <thread>


int main()
{
    std::atomic<bool> running{ true };
    App app(running);

	boost::asio::io_context io;
    auto work_guard = boost::asio::make_work_guard(io);

    auto server = std::make_shared<TcpServer>(io, config::ADDRESS, config::PORT);
    server->Accept();

    std::thread io_thread([&io]() {
        io.run();
	    });

    while (running.load()) {
		app.Run();
    }

    work_guard.reset();
    io.stop();

    if (io_thread.joinable()) {
        io_thread.join();
    }

    return 0;
}