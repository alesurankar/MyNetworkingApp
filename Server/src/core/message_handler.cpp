#include "message_handler.hpp"

#include <mutex>
#include <string>


void MessageHandler::AppToHandler(const std::string& message)
{
	std::lock_guard<std::mutex> lock(mtxAppToNet_);
	appToNetMessages_.push(message);
}

std::string MessageHandler::HandlerToNet()
{
	std::lock_guard<std::mutex> lock(mtxAppToNet_);
	if (appToNetMessages_.empty()) {
		return "";
	}
	std::string msg = std::move(appToNetMessages_.front());
	appToNetMessages_.pop();
	return msg;
}

void MessageHandler::NetToHandler(const std::string& message)
{
	std::lock_guard<std::mutex> lock(mtxNetToApp_);
	netToAppMessages_.push(message);
}

std::string MessageHandler::HandlerToApp()
{
	std::lock_guard<std::mutex> lock(mtxNetToApp_);

	if (netToAppMessages_.empty()) {
		return "";
	}
	std::string msg = std::move(netToAppMessages_.front());
	netToAppMessages_.pop();
	return msg;
}
