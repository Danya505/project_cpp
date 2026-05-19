#include "log.h"
#include <thread>
#include <chrono>

int main()
{
    Log *log = Log::instance();
    log->message(TAG::LOG_NORMAL, "program loaded");
    std::this_thread::sleep_for(std::chrono::seconds(19));
    log->message(TAG::LOG_ERROR, "error happens! help me!");
    log->print();
    return 0;
}