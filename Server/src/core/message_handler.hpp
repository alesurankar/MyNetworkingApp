#pragma once
#include <mutex>
#include <string>
#include <queue>

class MessageHandler
{
public:
	MessageHandler();
	void ServerToMSG(const std::string& message);
	std::string MSGToApp();
	void AppToMSG(const std::string& response);
	std::string MSGToServer();
private:
	std::mutex mtxIn_;
	std::mutex mtxOut_;
	std::string msg_;
	std::string validResponse_;
	std::queue<std::string> appMessages_;
};