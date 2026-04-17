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

    if (onSend_) {
        onSend_(msg);
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

// Callbacks
void App::SetSendHandler(SendHandler handler)
{
    onSend_ = std::move(handler);
}

void App::SetShutdownHandler(std::function<void()> handler)
{
    onShutdown_ = std::move(handler);
}