#pragma once
#include <atomic>
#include <memory>
#include <string>


class MessageHandler;

class App
{
public:
	App(std::atomic<bool>& running, std::shared_ptr<MessageHandler> msgHandler);
	void Run();
private:
	void TakeInput();
	void Process();
	void PushOutput();
private:
	std::atomic<bool>& running_;
	std::string input_;
	std::string output_;
	std::shared_ptr<MessageHandler> msgHandler_;
};