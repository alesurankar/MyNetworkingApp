#include "app.hpp"
#include <atomic>


int main()
{
    std::atomic<bool> running{ true };
    App app(running);

    while (running) {
        app.Run();
    }

    return 0;
}