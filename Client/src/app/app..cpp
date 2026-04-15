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
	msgHandler_(std::move(msgHandler))
{
	inputThread_ = std::thread(&App::InputLoop, this);
	updateThread_ = std::thread(&App::UpdateLoop, this);
}

App::~App()
{
	if (inputThread_.joinable()) {
		inputThread_.join();
	}
	if (updateThread_.joinable()) {
		updateThread_.join();
	}
}


///////////////////////////////////////////////
// Input thread
void App::InputLoop()
{
	while (running_.load()) {
		CaptureInput();
		SetMessageForMSG();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void App::CaptureInput()
{
}

void App::SetMessageForMSG()
{
	std::string msgOut;
	std::lock_guard<std::mutex> lock(mtxOut_);
	if (!outgoingMessages_.empty()) {
		msgOut = outgoingMessages_.front();
		outgoingMessages_.pop();
		msgHandler_->AppToHandler(msgOut);
		std::cout << "Step8. '" << msgOut << "' poped from queue... App::SetMessageForMSG (main thread)\n";
	}
}


///////////////////////////////////////////////
// Update thread
void App::UpdateLoop()
{
	while (running_.load()) {
		TakeFromQueue();
		PushToQueue();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void App::TakeFromQueue()
{
	std::lock_guard<std::mutex> lock(mtxIn_);
	if (!incomingMessages_.empty()) {
		message_ = incomingMessages_.front();
		incomingMessages_.pop();
		std::cout << "Step5. '" << message_ << "' poped from queue... App::TakeFromQueue (update thread)\n";
	}
}

void App::PushToQueue()
{
	std::lock_guard<std::mutex> lock(mtxOut_);
	if (!response_.empty()) {
		outgoingMessages_.push(response_);
		std::cout << "Step7. '" << response_ << "' pushed to queue... App::PushToQueue (update thread)\n";
		response_.clear();
	}
}


///////////////////////////////////////////////
// Main thread
void App::Run()
{
	GetMessageFromMSG();
	ShowOutput();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void App::GetMessageFromMSG()
{
	std::string msgIn = msgHandler_->HandlerToApp();
	std::lock_guard<std::mutex> lock(mtxIn_);
	if (!msgIn.empty()) {
		incomingMessages_.push(msgIn);
		std::cout << "Step4. '" << msgIn << "' pushed to queue... App::GetMessageFromMSG (main thread)\n";
	}
}

void App::ShowOutput()
{
}
