#include "log.h"
#include <vector>
#include <iostream>

Log *Log::instance()
{
    static Log inst;
    return &inst;
}

Log::Log()
{
}

void Log::message(TAG tag, std::string text)
{
    Time currentTime;
    events.push_back(Info(tag, text, currentTime));
}

void Log::print()
{
    int i = 0;
    for (Info &event : events)
    {
        if (i == 10)
            break;
        event.print_info();
        std::cout << std::endl;
        ++i;
    }
}