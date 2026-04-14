#include "app.hpp"
#include <core/message_handler.hpp>

#include <iostream>
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
{}

App::~App()
{
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
	std::string msgIn = msgHandler_->MSGToApp();
	std::lock_guard<std::mutex> lock(mtxIn_);
	if (!msgIn.empty()) {
		msgToUpdate_.push(msgIn);
		std::cout << "Step4. '" << msgIn << "' pushed to queue... App::GetMessageFromMSG (main thread)\n";
	}
}

void App::SetMessageForMSG()
{
	std::string msgOut;
	std::lock_guard<std::mutex> lock(mtxOut_);
	if (!msgIsUpdated_.empty()) {
		msgOut = msgIsUpdated_.front();
		msgIsUpdated_.pop();
		msgHandler_->AppToMSG(msgOut);
		std::cout << "Step8. '" << msgOut << "' poped from queue... App::SetMessageForMSG (main thread)\n";
	}
}