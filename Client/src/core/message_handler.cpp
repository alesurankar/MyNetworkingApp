#include "message_handler.hpp"

#include <iostream>
#include <mutex>
#include <string>


void MessageHandler::AppToMSG(const std::string& message)
{
    std::lock_guard<std::mutex> lock(mtxIn_);
    appMessages_.push(message);
    std::cout << "Step2000. '" << message << "' pushed to queue... MessageHandler::AppToMSG\n";
}

std::string MessageHandler::MSGToClient()
{
    {
        std::lock_guard<std::mutex> lock(mtxIn_);
        if (!appMessages_.empty()) {
            msg_ = appMessages_.front() + "\n";
            appMessages_.pop();
            std::cout << "Step3000. '" << msg_ << "' poped from queue... MessageHandler::MSGToClient\n";
        }
        else {
            msg_.clear();
        }
    }
    return msg_;
}

void MessageHandler::ClientToMSG(const std::string& response)
{
    std::lock_guard<std::mutex> lock(mtxOut_);
    validResponse_ = response;
}

std::string MessageHandler::MSGToApp()
{
    std::lock_guard<std::mutex> lock(mtxOut_);
    if (validResponse_.empty()) {
        return "";
    }
    const std::string messageToApp = validResponse_;
    std::cout << "Step9000. '" << messageToApp << "' read from server... MessageHandler::MSGToApp\n";
    return messageToApp;
}