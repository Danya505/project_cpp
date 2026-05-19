#include "check_point.h"
#include <sstream>
#include <iomanip>

CheckPoint::CheckPoint(const std::string &name, const Coordinates &coords)
    : name(name), coords(coords) {}

std::string CheckPoint::getName() const
{
    return name;
}

Coordinates CheckPoint::getCoords() const
{
    return coords;
}

MandatoryCheckPoint::MandatoryCheckPoint(const std::string &name, const Coordinates &coords)
    : CheckPoint(name, coords) {}

std::string MandatoryCheckPoint::getPenaltyString() const
{
    return "незачёт СУ";
}

double MandatoryCheckPoint::getPenaltyValue() const
{
    return 0.0;
}

OptionalCheckPoint::OptionalCheckPoint(const std::string &name, const Coordinates &coords, double penaltyHours)
    : CheckPoint(name, coords), penalty(penaltyHours) {}

std::string OptionalCheckPoint::getPenaltyString() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << penalty << " ч";
    return oss.str();
}

double OptionalCheckPoint::getPenaltyValue() const
{
    return penalty;
}