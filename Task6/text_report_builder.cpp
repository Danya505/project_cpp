#include "text_report_builder.h"
#include "check_point.h"
#include <sstream>
#include <iomanip>

void TextReportBuilder::addCheckPoint(int index, const CheckPoint &cp)
{
    std::ostringstream line;
    line << std::fixed << std::setprecision(6);
    line << index << ". "
         << cp.getName() << "; "
         << "lat=" << cp.getCoords().latitude << "; "
         << "lon=" << cp.getCoords().longitude << "; "
         << "штраф=" << cp.getPenaltyString();

    lines.push_back(line.str());
}

std::string TextReportBuilder::getResult() const
{
    std::ostringstream result;
    for (const auto &line : lines)
    {
        result << line << "\n";
    }
    return result.str();
}