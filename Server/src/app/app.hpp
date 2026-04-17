#pragma once
#include <string>
#include <functional>
#include <cstdint>


class App
{
public:
	void OnMessage(uint64_t id, const std::string& msg);
	void SetShutdownHandler(std::function<void()> handler);
private:
	std::function<void()> onShutdown_;
};