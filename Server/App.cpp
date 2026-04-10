#include "App.h"
#include <iostream>


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
	std::cout << "App is running...\n";
}
