#include "app.hpp"

#include <iostream>
#include <utility>
#include <string>
#include <cstdint>


void App::Run()
{
    if (hasNewMessage_) {
        current_ = std::move(pending_);
        hasNewMessage_ = false;
    }

    Process();
}

void App::OnMessage(uint64_t id, const std::string& msg)
{
    std::cout << "MSG RECEIVED from " << id << ": " << msg << "\n";
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
