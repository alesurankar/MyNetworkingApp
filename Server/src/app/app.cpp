#include "app.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>


App::App(std::atomic<bool>& runFlag)
	:
	running_(runFlag)
{
}

App::~App()
{
}

void App::Run()
{
	UpdateLoop();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void App::UpdateLoop()
{
	if (cycle >= 5) {
		std::cout << "Stopping server...\n";
		running_ = false;
		cycle = 0;
	}
	else {
		std::cout << "Server is running...\n";
		cycle++;
	}
}
