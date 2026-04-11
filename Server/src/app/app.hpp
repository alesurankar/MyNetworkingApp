#pragma once
#include <atomic>

class App
{
public:
	App(std::atomic<bool>& runFlag);
	~App();
	void Run();
private:
	void UpdateLoop();
private:
	std::atomic<bool>& running_;
	int cycle = 0;
};