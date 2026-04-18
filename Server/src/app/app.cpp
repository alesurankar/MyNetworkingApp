#include "app.hpp"

#include <iostream>
#include <utility>
#include <string>
#include <cstdint>
#include <functional>


void App::OnMessage(uint64_t id, const std::string& msg)
{
    std::cout << "MSG RECEIVED from ID: " << id << ": " << msg << "\n";
}

// callbacks
void App::SetShutdownHandler(std::function<void()> handler)
{
    onShutdown_ = std::move(handler);
}