#pragma once
#include <string>
#include <functional>
#include <cstdint>


class App
{
public:
	using MessageHandler = std::function<void(const std::string&)>;

	void OnMessage(uint64_t id, const std::string& msg);
	void SetShutdownHandler(std::function<void()> handler);
private:
	std::string output_;
	std::string current_;
	std::string pending_;
	bool hasNewMessage_ = false;
	MessageHandler onMessage_;
	std::function<void()> onShutdown_;
};