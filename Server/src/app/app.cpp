#include "app.hpp"
#include <core/message_handler.hpp>

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <memory>
#include <utility>
#include <string>
#include <mutex>


App::App(std::atomic<bool>& running, std::shared_ptr<MessageHandler> msgHandler)
	:
	running_(running),
	msgHandler_(std::move(msgHandler)),
	nextFrame_(true)
{
	updateThread_ = std::thread(&App::UpdateLoop, this);
}

App::~App()
{
	if (updateThread_.joinable()) {
		updateThread_.join();
	}
}

void App::Run()
{
	if (nextFrame_.load()) {
		GetMessageFromMSG();
		SetMessageForMSG();
		nextFrame_.store(false);
	}
}

void App::GetMessageFromMSG()
{
	std::string msgIn = msgHandler_->HandlerToApp();
	std::lock_guard<std::mutex> lock(mtxIn_);
	if (!msgIn.empty()) {
		msgToUpdate_.push(msgIn);
		std::cout << "Step4. '"<< msgIn << "' pushed to queue... App::GetMessageFromMSG (main thread)\n";
	}
}

void App::SetMessageForMSG()
{
	std::string msgOut;
	std::lock_guard<std::mutex> lock(mtxOut_);
	if (!msgIsUpdated_.empty()) {
		msgOut = msgIsUpdated_.front();
		msgIsUpdated_.pop();
		msgHandler_->AppToHandler(msgOut);
		std::cout << "Step8. '" << msgOut << "' poped from queue... App::SetMessageForMSG (main thread)\n";
	}
}


///////////////////////////////////////////////
void App::UpdateLoop()
{
	while (running_.load()) {
		TakeFromQueue();
		UpdateParameters();
		PushToQueue();

		nextFrame_.store(true);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void App::TakeFromQueue()
{
	std::lock_guard<std::mutex> lock(mtxIn_);
	if (!msgToUpdate_.empty()) {
		message_ = msgToUpdate_.front();
		msgToUpdate_.pop();
		std::cout << "Step5. '" << message_ << "' poped from queue... App::TakeFromQueue (update thread)\n";
	}
}

void App::UpdateParameters()
{
	if (!message_.empty()) {
		// TODO : Update parameters based on the message
		response_ = message_ + " is processed.";
		message_.clear();
	}
}

void App::PushToQueue()
{
	std::lock_guard<std::mutex> lock(mtxOut_);
	if (!response_.empty()) {
		msgIsUpdated_.push(response_);
		std::cout << "Step7. '" << response_ << "' pushed to queue... App::PushToQueue (update thread)\n";
		response_.clear();
	}
}
