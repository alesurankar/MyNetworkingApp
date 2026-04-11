#include <app/app.hpp>
#include <networking/tcp_server.hpp>

#include <boost/asio/io_context.hpp>

#include <atomic>
#include <memory>
#include <thread>


int main()
{
	std::unique_ptr<TcpServer> server_;
    std::atomic<bool> running_{ true };
    App app(running_);

	boost::asio::io_context io;
	server_ = std::make_unique<TcpServer>(io, "127.0.0.1", 12345);
    server_->Accept();

    std::thread io_thread([&io]() {
        io.run();
		});

    while (running_) {
		app.Run();
    }

    io.stop();

    if (io_thread.joinable()) {
        io_thread.join();
    }

    return 0;
}