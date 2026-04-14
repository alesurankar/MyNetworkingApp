#include "message_handler.hpp"

#include <iostream>
#include <mutex>
#include <string>


void MessageHandler::AppToHandler(const std::string& message)
{
	std::lock_guard<std::mutex> lock(mtxAppToNet_);
	appToNetMessages_.push(message);
	std::cout << "Step20000. '" << message << "' pushed to queue... MessageHandler::AppToMSG\n";
}

std::string MessageHandler::HandlerToNet()
{
	std::lock_guard<std::mutex> lock(mtxAppToNet_);
	if (appToNetMessages_.empty()) {
		return "";
	}
	std::string msg = std::move(appToNetMessages_.front());
	appToNetMessages_.pop();
	std::cout << "Step9. '" << msg << "' read from server... MessageHandler::MSGToServer\n";
	return msg;
}

void MessageHandler::NetToHandler(const std::string& message)
{
	std::lock_guard<std::mutex> lock(mtxNetToApp_);
	netToAppMessages_.push(message);
	std::cout << "Step2. '" << message << "' pushed to queue... MessageHandler::ServerToMSG\n";
}

std::string MessageHandler::HandlerToApp()
{
	std::lock_guard<std::mutex> lock(mtxNetToApp_);

	if (netToAppMessages_.empty()) {
		return "";
	}
	std::string msg = std::move(netToAppMessages_.front());
	std::cout << "Step3. '" << msg << "' poped from queue... MessageHandler::MSGToApp\n";
	netToAppMessages_.pop();
	return msg;
}
