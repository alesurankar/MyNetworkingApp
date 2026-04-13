#include "message_handler.hpp"

#include <mutex>
#include <string>


MessageHandler::MessageHandler()
{
}

void MessageHandler::ServerToMSG(const std::string& message)
{
	std::lock_guard<std::mutex> lock(mtxIn_);
	app_messages_.push(message);
}

std::string MessageHandler::MSGToApp()
{
	{
		std::lock_guard<std::mutex> lock(mtxIn_);
		if (!app_messages_.empty()) {
			msg_ = app_messages_.front();
			app_messages_.pop();
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