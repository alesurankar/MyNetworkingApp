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
	msgHandler_(std::move(msgHandler)),
	nextFrame_(true)
{
}

void App::Run()
{
	if (nextFrame_.load()) {
		GetMessageFromMSG();
		SetMessageForMSG();
		nextFrame_.store(false);
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void App::GetMessageFromMSG()
{
	std::string msgIn = msgHandler_->MSGToApp();
	if (!msgIn.empty()) {
		msgToUpdate_.push(msgIn);
		std::cout << "Step4. '"<< msgIn << "' pushed to queue... App::GetMessageFromMSG (app thread)\n\n";
	}
}

void App::SetMessageForMSG()
{
	std::string msgOut;
	std::cout << "App::SetMessage(): msgIsUpdated_.size(): " << msgIsUpdated_.size() << "\n";
	if (!msgIsUpdated_.empty()) {
		msgOut = msgIsUpdated_.front();
		msgIsUpdated_.pop();
		msgHandler_->AppToMSG(msgOut);
	}
}
