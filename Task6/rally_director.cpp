#include "rally_director.h"
#include "check_point.h"
#include "report_builder.h"

void RallyDirector::process(const std::vector<std::unique_ptr<CheckPoint>> &checkpoints,
                            ReportBuilder &builder)
{
    for (size_t i = 0; i < checkpoints.size(); ++i)
    {
        builder.addCheckPoint(static_cast<int>(i + 1), *checkpoints[i]);
    }
}