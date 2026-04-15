#pragma once
#include <mutex>
#include <string>
#include <queue>

class MessageHandler
{
public:
	MessageHandler() = default;
	void AppToHandler(const std::string& response);
	std::string HandlerToNet();
	void NetToHandler(const std::string& message);
	std::string HandlerToApp();
private:
	std::mutex mtxAppToNet_;
	std::mutex mtxNetToApp_;
	std::queue<std::string> netToAppMessages_;
	std::queue<std::string> appToNetMessages_;
};