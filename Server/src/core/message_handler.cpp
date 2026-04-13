#include "message_handler.hpp"

#include <iostream>
#include <mutex>
#include <string>


MessageHandler::MessageHandler()
{
}

void MessageHandler::ServerToMSG(const std::string& message)
{
	std::lock_guard<std::mutex> lock(mtxIn_);
	appMessages_.push(message);
	std::cout << "Step2. '" << message << "' pushed to queue... MessageHandler::ServerToMSG\n";
}

std::string MessageHandler::MSGToApp()
{
	{
		std::lock_guard<std::mutex> lock(mtxIn_);
		if (!appMessages_.empty()) {
			msg_ = appMessages_.front();
			appMessages_.pop();
			std::cout << "Step3. '" << msg_ << "' poped from queue... MessageHandler::MSGToApp\n";
		}
		else {
			msg_.clear();
		}
	}
	return msg_;
}

void MessageHandler::AppToMSG(const std::string& response)
{
	std::lock_guard<std::mutex> lock(mtxOut_);
	validResponse_ = response;
}

std::string MessageHandler::MSGToServer()
{
	std::lock_guard<std::mutex> lock(mtxOut_);
	std::string messageToServer = validResponse_ + "\n";
	validResponse_.clear();

	return messageToServer;
}