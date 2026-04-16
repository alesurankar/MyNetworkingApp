#pragma once
#include <cstdint>
#include <string>


struct Message
{
    uint64_t clientId;
    std::string payload;
};