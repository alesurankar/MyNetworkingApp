#pragma once
#include <atomic>
#include <memory>
#include <string>
#include <thread>

class MessageHandler;

class App
{
public:
	App(std::atomic<bool>& running, std::shared_ptr<MessageHandler> msgHandler);
	~App();
	void Run();
private:
	void InputLoop();
	std::string CaptureInput();
	void ShowOutput(const std::string& msg);
private:
	std::atomic<bool>& running_;
	std::thread inputThread_;
	std::shared_ptr<MessageHandler> msgHandler_;
};