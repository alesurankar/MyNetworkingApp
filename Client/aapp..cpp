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
	std::cout << "Client is running...\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));
}
