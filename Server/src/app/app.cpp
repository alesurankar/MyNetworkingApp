#include "app.hpp"
#include <core/message_handler.hpp>

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <memory>


App::App(std::atomic<bool>& running, std::shared_ptr<MessageHandler> msgHandler)
	:
	running_(running),
	msgHandler_(msgHandler)
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
	std::cout << "Server is running...\n";
}
