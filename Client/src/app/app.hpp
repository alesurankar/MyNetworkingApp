#pragma once
#include <atomic>
#include <string>


class App
{
public:
	App(std::atomic<bool>& running);
	void Run();
private:
	void ShowOutput(const std::string& msg);
	void InputLoop();
	std::string CaptureInput();
private:
	std::atomic<bool>& running_;
};