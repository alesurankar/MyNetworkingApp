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
	int i = 0;
	while (i < 4) {
		std::cout << "Server is running...\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		i++;
	}
	running_ = false;
}
