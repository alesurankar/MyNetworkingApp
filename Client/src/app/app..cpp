#include "app.hpp"

#include <atomic>
#include <string>
#include <utility>


App::App(std::atomic<bool>& running)
	:
	running_(running)
{}

void App::Run()
{
	Process();
}

void App::OnInput(const std::string& msg)
{
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