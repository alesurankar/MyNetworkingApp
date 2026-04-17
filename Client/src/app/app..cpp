#include "app.hpp"

#include <iostream>
#include <string>
#include <utility>
#include <functional>


void App::OnUserInput(const std::string& msg)
{
    std::cout << "Sending to server: " << msg << "\n";
    if (msg == "quit") {
        if (onShutdown_) {
            onShutdown_();
        }
        return;
    }

    if (out_) {
        out_(msg);
    }
}

void App::OnNetworkMessage(const std::string& msg)
{
    std::cout << "Received from server: " << msg << "\n";
    if (msg == "quit") {
        if (onShutdown_) {
            onShutdown_();
        }
        return;
    }
}

void App::SetOutputHandler(OutHandler handler)
{
    out_ = std::move(handler);
}

void App::SetShutdownHandler(std::function<void()> handler)
{
    onShutdown_ = std::move(handler);
}