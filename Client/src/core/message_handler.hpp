#pragma once
#include <mutex>
#include <string>
#include <queue>

class MessageHandler
{
public:
    MessageHandler() = default;
    void AppToMSG(const std::string& message);
    std::string MSGToClient();
    void ClientToMSG(const std::string& response);
    std::string MSGToApp();
private:
    std::mutex mtxIn_;
    std::mutex mtxOut_;
    std::string msg_;
    std::string validResponse_;
    std::queue<std::string> appMessages_;
};