#pragma once
#include <atomic>

class App
{
public:
	App(std::atomic<bool>& running);
	~App();
	void Run();
private:
	void Update();
private:
	std::atomic<bool>& running_;
	int cycle = 0;
};