#include "time.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

Time::Time()
{
    std::time_t now = std::time(nullptr);
    std::tm *now_tm = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");
    time = oss.str();
}

void Time::print_time()
{
    std::cout << time;
}