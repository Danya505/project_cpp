#pragma once

#include <string>
#include <vector>
#include <ctime>
#include "tag.h"
#include "info.h"

class Log
{
public:
    static Log *instance();
    void message(TAG tag, std::string text);
    void print();

private:
    Log();
    Log(const Log &) = delete;
    Log &operator=(const Log &) = delete;

    std::vector<Info> events;
};