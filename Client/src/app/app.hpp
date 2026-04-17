#pragma once
#include <string>
#include <queue>
#include <functional>


class App
{
public:
    using OutHandler = std::function<void(const std::string&)>;
    void Run();
    void OnInput(const std::string& msg);
    void SetOutputHandler(OutHandler handler);
    void SetShutdownHandler(std::function<void()> handler);
private:
    void Process();
private:
    std::queue<std::string> inbox_;
    std::string current_;
    OutHandler out_;
    std::function<void()> onShutdown_;
};