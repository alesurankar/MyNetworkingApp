#include "app.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>


App::App(std::atomic<bool>& running)
	:
	running_(running)
{
}

App::~App()
{
}

void App::Run()
{
	Update();
	std::this_thread::sleep_for(std::chrono::seconds(10));
}

void App::Update()
{
	//if (cycle >= 5) {
	//	std::cout << "Stopping client...\n";
	//	running_.store(false);
	//	cycle = 0;
	//}
	//else {
		std::cout << "Client is running...\n";
	//	cycle++;
	//}
}
