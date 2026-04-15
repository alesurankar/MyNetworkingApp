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
{}

void App::Run()
{
	TakeInput();
	Process();
	PushOutput();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void App::TakeInput()
{
	input_ = msgHandler_->HandlerToApp();
	if (!input_.empty()) {
		std::cout << "Received from network: " << input_ << "\n";
	}
}

void App::Process()
{
	// TODO : Update parameters based on the message
	if (!input_.empty()) {
		output_ = input_ + " is processed.";
		input_.clear();
	}
}

void App::PushOutput()
{
	if (!output_.empty()) {
		std::cout << "Sending to network: " << output_ << "\n";
		msgHandler_->AppToHandler(std::move(output_));
		output_.clear();
	}
}
