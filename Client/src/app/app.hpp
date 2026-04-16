#pragma once
#include <atomic>
#include <string>
#include <queue>
#include <functional>


class App
{
public:
    using OutHandler = std::function<void(const std::string&)>;

    App(std::atomic<bool>& running);
    void Run();
    void OnInput(const std::string& msg);
    void SetOutputHandler(OutHandler handler);
private:
    void Process();
private:
    std::atomic<bool>& running_;
    std::queue<std::string> inbox_;
    std::string current_;
    OutHandler out_;
};