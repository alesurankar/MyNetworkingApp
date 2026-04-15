#pragma once
#include <atomic>
#include <memory>
#include <string>
#include <thread>

class MessageChannel;

class App
{
public:
	App(std::atomic<bool>& running, std::shared_ptr<MessageChannel> msgChannel);
	~App();
	void Run();
private:
	void ShowOutput(const std::string& msg);
	void InputLoop();
	std::string CaptureInput();
private:
	std::atomic<bool>& running_;
	std::thread inputThread_;
	std::shared_ptr<MessageChannel> msgChannel_;
};