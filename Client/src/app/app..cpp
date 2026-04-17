#include "app.hpp"

#include <iostream>
#include <string>
#include <utility>


void App::Run()
{
	Process();
}

void App::OnInput(const std::string& msg)
{
    std::cout << "MSG RECEIVED: " << msg << "\n";
    if (msg == "quit") {
        if (onShutdown_) {
            onShutdown_();
        }
        return;
    }

	inbox_.push(msg);
}

void App::SetOutputHandler(OutHandler handler)
{
    out_ = std::move(handler);
}

void App::Process()
{
    while (!inbox_.empty()) {
        current_ = inbox_.front();
        inbox_.pop();

        std::string response = "processed: " + current_;

        if (out_) {
            out_(response);
        }
    }
}

void App::SetShutdownHandler(std::function<void()> handler)
{
    onShutdown_ = std::move(handler);
}