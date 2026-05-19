#include "info.h"
#include "time.h"
#include "tag.h"
#include <iostream>

Info::Info(TAG tag, std::string text, Time time)
{
    this->tag = tag;
    this->text = text;
    this->time = time;
}

void Info::print_info()
{
    std::cout << "TAG: " << tag << ", "
              << "MESSAGE: " << text << ", ";
    time.print_time();
}