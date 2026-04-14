#pragma once
#include <atomic>
#include <memory>
#include <queue>
#include <string>
#include <mutex>

class MessageHandler;

class App
{
public:
	App(std::atomic<bool>& running, std::shared_ptr<MessageHandler> msgHandler);
	~App();
	void Run();
private:
	void GetMessageFromMSG();
	void SetMessageForMSG();
private:
	std::atomic<bool>& running_;
	std::atomic<bool> nextFrame_;
	std::mutex mtxIn_;
	std::mutex mtxOut_;
	std::shared_ptr<MessageHandler> msgHandler_;
	std::queue<std::string> msgToUpdate_;
	std::queue<std::string> msgIsUpdated_;
};