#pragma once

#include <ctime>
#include "time.h"
#include "tag.h"

class Info
{
private:
    TAG tag;
    std::string text;
    Time time;

public:
    Info(TAG tag, std::string text, Time time);
    void print_info();
};