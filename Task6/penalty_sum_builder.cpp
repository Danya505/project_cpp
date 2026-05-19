#include "penalty_sum_builder.h"
#include "check_point.h"
#include <sstream>
#include <iomanip>

void PenaltySumBuilder::addCheckPoint(int /*index*/, const CheckPoint &cp)
{
    totalPenalty += cp.getPenaltyValue();
}

std::string PenaltySumBuilder::getResult() const
{
    std::ostringstream result;
    result << std::fixed << std::setprecision(2)
           << "Суммарный штраф по необязательным КП: " << totalPenalty << " ч";
    return result.str();
}