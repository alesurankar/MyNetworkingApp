#pragma once
#include <atomic>
#include <memory>
#include <queue>
#include <string>
#include <thread>
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
	void UpdateLoop();
	void TakeFromQueue();
	void UpdateParameters();
	void PushToQueue();
private:
	std::atomic<bool>& running_;
	std::atomic<bool> nextFrame_;
	std::string message_;
	std::string response_;
	std::thread updateThread_;
	std::mutex mtxIn_;
	std::mutex mtxOut_;
	std::shared_ptr<MessageHandler> msgHandler_;
	std::queue<std::string> msgToUpdate_;
	std::queue<std::string> msgIsUpdated_;
};