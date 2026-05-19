#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <string>
#include <memory>

struct Coordinates
{
    double latitude;
    double longitude;
};

class CheckPoint
{
public:
    CheckPoint(const std::string &name, const Coordinates &coords);
    virtual ~CheckPoint() = default;
    std::string getName() const;
    Coordinates getCoords() const;
    virtual std::string getPenaltyString() const = 0;
    virtual double getPenaltyValue() const = 0;

private:
    std::string name;
    Coordinates coords;
};

class MandatoryCheckPoint : public CheckPoint
{
public:
    MandatoryCheckPoint(const std::string &name, const Coordinates &coords);
    std::string getPenaltyString() const override;
    double getPenaltyValue() const override;
};

class OptionalCheckPoint : public CheckPoint
{
public:
    OptionalCheckPoint(const std::string &name, const Coordinates &coords, double penaltyHours);
    std::string getPenaltyString() const override;
    double getPenaltyValue() const override;

private:
    double penalty;
};

#endif