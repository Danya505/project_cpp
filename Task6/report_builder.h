#ifndef REPORTBUILDER_H
#define REPORTBUILDER_H

#include <string>
#include "check_point.h"

class ReportBuilder
{
public:
    virtual ~ReportBuilder() = default;

    virtual void addCheckPoint(int index, const CheckPoint &cp) = 0;
    virtual std::string getResult() const = 0;
};

#endif