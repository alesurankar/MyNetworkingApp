#pragma once
#include <atomic>
#include <string>


class App
{
public:
	App(std::atomic<bool>& running);
	void OnMessage(const std::string& msg);
	void Run();
private:
	void Process();
private:
	std::atomic<bool>& running_;
	std::string output_;
	std::string current_;
	std::string pending_;
	bool hasNewMessage_ = false;
};