#pragma once
#include <mutex>
#include <string>
#include <queue>


class MessageChannel
{
public:
	MessageChannel() = default;
	void AppToChannel(const std::string& response);
	std::string ChannelToNet();
	void NetToChannel(const std::string& message);
	std::string ChannelToApp();
private:
	std::mutex mtxAppToNet_;
	std::mutex mtxNetToApp_;
	std::queue<std::string> netToAppMessages_;
	std::queue<std::string> appToNetMessages_;
};