#include "app.hpp"

#include <atomic>
#include <utility>
#include <string>


App::App(std::atomic<bool>& running)
	:
	running_(running)
{}

void App::Run()
{
    if (hasNewMessage_) {
        current_ = std::move(pending_);
        hasNewMessage_ = false;
    }

    Process();
}

void App::OnMessage(const std::string& msg)
{
    pending_ = msg;
    hasNewMessage_ = true;
}

void App::Process()
{
    if (!current_.empty()) {
        output_ = current_ + " is processed.";
        current_.clear();
    }
}
