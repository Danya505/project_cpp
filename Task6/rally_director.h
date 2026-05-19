#ifndef RALLYDIRECTOR_H
#define RALLYDIRECTOR_H

#include <vector>
#include <memory>

class CheckPoint;
class ReportBuilder;

class RallyDirector
{
public:
    void process(const std::vector<std::unique_ptr<CheckPoint>> &checkpoints,
                 ReportBuilder &builder);
};

#endif