#include <core/message_channel.hpp>

#include <mutex>
#include <string>
#include <utility>


void MessageChannel::AppToChannel(const std::string& message)
{
	std::lock_guard<std::mutex> lock(mtxAppToNet_);
	appToNetMessages_.push(message);
}

std::string MessageChannel::ChannelToNet()
{
	std::lock_guard<std::mutex> lock(mtxAppToNet_);
	if (appToNetMessages_.empty()) {
		return "";
	}
	std::string msg = std::move(appToNetMessages_.front());
	appToNetMessages_.pop();
	return msg;
}

void MessageChannel::NetToChannel(const std::string& message)
{
	std::lock_guard<std::mutex> lock(mtxNetToApp_);
	netToAppMessages_.push(message);
}

std::string MessageChannel::ChannelToApp()
{
	std::lock_guard<std::mutex> lock(mtxNetToApp_);

	if (netToAppMessages_.empty()) {
		return "";
	}
	std::string msg = std::move(netToAppMessages_.front());
	netToAppMessages_.pop();
	return msg;
}
