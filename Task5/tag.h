#pragma once
#include <iostream>

enum class TAG
{
    LOG_NORMAL = 1,
    LOG_REMARK = 2,
    LOG_ERROR = 3
};

inline std::ostream &operator<<(std::ostream &os, const TAG &tag)
{
    switch (tag)
    {
    case TAG::LOG_NORMAL:
        os << "LOG_NORMAL";
        break;
    case TAG::LOG_REMARK:
        os << "LOG_REMARK";
        break;
    case TAG::LOG_ERROR:
        os << "LOG_ERROR";
        break;
    }
    return os;
}