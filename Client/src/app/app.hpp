#pragma once
#include <atomic>

class App
{
public:
	App(std::atomic<bool>& running);
	~App();
	void Run();
private:
	std::atomic<bool>& running_;
};