#include "app.hpp"
#include "tcp_server.hpp"

#include <atomic>
#include <memory>


int main()
{
	std::unique_ptr<TcpServer> server_;
    std::atomic<bool> running_ = true;
    App app(running_);

    while (running_) {
		app.Run();
    }

    return 0;
}