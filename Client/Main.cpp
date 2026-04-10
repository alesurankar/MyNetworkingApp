#include "App.h"
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