#ifndef TEXTREPORTBUILDER_H
#define TEXTREPORTBUILDER_H

#include "report_builder.h"
#include <vector>
#include <string>

class TextReportBuilder : public ReportBuilder
{
public:
    void addCheckPoint(int index, const CheckPoint &cp) override;
    std::string getResult() const override;

private:
    std::vector<std::string> lines;
};

#endif