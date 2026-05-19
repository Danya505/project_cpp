#ifndef PENALTYSUMBUILDER_H
#define PENALTYSUMBUILDER_H

#include "report_builder.h"
#include <string>

class PenaltySumBuilder : public ReportBuilder
{
public:
    void addCheckPoint(int index, const CheckPoint &cp) override;
    std::string getResult() const override;

private:
    double totalPenalty = 0.0;
};

#endif