#pragma once
#include <string>
#include <functional>


class App
{
public:
    using SendHandler = std::function<void(const std::string&)>;

    void OnUserInput(const std::string& msg);
    void OnNetworkMessage(const std::string& msg);
    void SetSendHandler(SendHandler handler);
    void SetShutdownHandler(std::function<void()> handler);
private:
    SendHandler onSend_;
    std::function<void()> onShutdown_;
};