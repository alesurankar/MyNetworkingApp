#pragma once
#include <atomic>
#include <memory>
#include <queue>
#include <string>
#include <mutex>
#include <thread>

class MessageHandler;

class App
{
public:
	App(std::atomic<bool>& running, std::shared_ptr<MessageHandler> msgHandler);
	~App();
private:
	// Input thread
	void InputLoop();
	void CaptureInput();
	void SetMessageForMSG();
	// Update thread
	void UpdateLoop();
	void TakeFromQueue();
	void PushToQueue();
	// Main thread
public:
	void Run();
private:
	void GetMessageFromMSG();
	void ShowOutput();
private:
	std::atomic<bool>& running_;
	std::string message_;
	std::string response_;
	std::thread inputThread_;
	std::thread updateThread_;
	std::mutex mtxIn_;
	std::mutex mtxOut_;
	std::shared_ptr<MessageHandler> msgHandler_;
	std::queue<std::string> incomingMessages_;
	std::queue<std::string> outgoingMessages_;
};