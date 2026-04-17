#pragma once
#include <string>
#include <functional>


class App
{
public:
    using OutHandler = std::function<void(const std::string&)>;
    void OnUserInput(const std::string& msg);
    void OnNetworkMessage(const std::string& msg);
    void SetOutputHandler(OutHandler handler);
    void SetShutdownHandler(std::function<void()> handler);
private:
    OutHandler out_;
    std::function<void()> onShutdown_;
};