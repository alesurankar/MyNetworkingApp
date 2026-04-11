#include <app/app.hpp>
#include <networking/tcp_client.hpp>
#include <Common/config.hpp>

#include <boost/asio/io_context.hpp>

#include <atomic>
#include <memory>
#include <thread>


int main()
{
	std::unique_ptr<TcpClient> client_;
    std::atomic<bool> running_{ true };
    App app(running_);

	boost::asio::io_context io;
    client_ = std::make_unique<TcpClient>(io, config::ADDRESS, config::PORT);
	client_->Connect();

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