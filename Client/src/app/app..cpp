#include "app.hpp"
#include <core/message_handler.hpp>

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


///////////////////////////////////////////////
// Input thread
void App::InputLoop()
{
	while (running_.load()) {
		std::string msg = CaptureInput();
		if (!msg.empty()) {
			msgHandler_->AppToHandler(msg);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

std::string App::CaptureInput()
{
}


///////////////////////////////////////////////
// Main thread
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
}
