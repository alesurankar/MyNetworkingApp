#include "app.hpp"
#include <include/core/message_channel.hpp>

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <memory>
#include <utility>
#include <string>


App::App(std::atomic<bool>& running, std::shared_ptr<MessageChannel> msgChannel)
	:
	running_(running),
	msgChannel_(std::move(msgChannel))
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
	input_ = msgChannel_->ChannelToApp();
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
		msgChannel_->AppToChannel(std::move(output_));
		output_.clear();
	}
}
