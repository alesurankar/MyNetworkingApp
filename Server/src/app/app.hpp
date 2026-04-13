#pragma once
#include <atomic>
#include <memory>

class MessageHandler;

class App
{
public:
	App(std::atomic<bool>& running, std::shared_ptr<MessageHandler> msgHandler);
	~App();
	void Run();
private:
	void Update();
private:
	std::atomic<bool>& running_;
	std::shared_ptr<MessageHandler> msgHandler_;
};