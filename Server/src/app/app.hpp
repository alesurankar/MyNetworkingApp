#pragma once
#include <atomic>
#include <memory>
#include <queue>
#include <string>

class MessageHandler;

class App
{
public:
	App(std::atomic<bool>& running, std::shared_ptr<MessageHandler> msgHandler);
	void Run();
private:
	void Update();
	void GetMessageFromMSG();
private:
	std::atomic<bool>& running_;
	std::string message_;
	std::shared_ptr<MessageHandler> msgHandler_;
	std::queue<std::string> msgToUpdate_;
};