#include "app.hpp"
#include <core/message_handler.hpp>

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <memory>
#include <utility>
#include <string>


App::App(std::atomic<bool>& running, std::shared_ptr<MessageHandler> msgHandler)
	:
	running_(running),
	msgHandler_(std::move(msgHandler))
{
	inputThread_ = std::thread(&App::InputLoop, this);
}

App::~App()
{
	if (inputThread_.joinable()) {
		inputThread_.join();
	}
}

void App::Run()
{
	std::string msg = msgHandler_->HandlerToApp();
	if (!msg.empty()) {
		ShowOutput(msg);
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void App::ShowOutput(const std::string& msg)
{
	std::cout << "output: " << msg << "\n";
}


///////////////////////////////////////////////
// Input thread
void App::InputLoop()
{
	while (running_.load()) {
		std::string msg = CaptureInput();
		if (!msg.empty()) {
			std::cout << "Step2. '" << msg << "' sending out from App::InputLoop\n";
			msgHandler_->AppToHandler(msg);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

std::string App::CaptureInput()
{
	std::string input;
	std::cin >> input;
	std::cout << "Step1. '" << input << "' captured in App::CaptureInput\n";
	return input;
}
