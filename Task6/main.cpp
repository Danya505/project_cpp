#include "check_point.h"
#include "text_report_builder.h"
#include "penalty_sum_builder.h"
#include "rally_director.h"
#include <iostream>
#include <vector>
#include <memory>

int main()
{

    std::vector<std::unique_ptr<CheckPoint>> checkpoints;

    checkpoints.push_back(std::make_unique<MandatoryCheckPoint>("Старт",
                                                                Coordinates{55.7558, 37.6176}));

    checkpoints.push_back(std::make_unique<OptionalCheckPoint>("Лесной участок",
                                                               Coordinates{55.7512, 37.6184}, 1.5));

    checkpoints.push_back(std::make_unique<MandatoryCheckPoint>("Мост",
                                                                Coordinates{55.7483, 37.6201}));

    checkpoints.push_back(std::make_unique<OptionalCheckPoint>("Болото",
                                                               Coordinates{55.7445, 37.6237}, 2.0));

    checkpoints.push_back(std::make_unique<MandatoryCheckPoint>("Финиш",
                                                                Coordinates{55.7400, 37.6300}));

    RallyDirector director;

    TextReportBuilder textBuilder;
    director.process(checkpoints, textBuilder);
    std::cout << "ТЕКСТОВЫЙ ОТЧЁТ:\n"
              << textBuilder.getResult() << std::endl;

    PenaltySumBuilder penaltyBuilder;
    director.process(checkpoints, penaltyBuilder);
    std::cout << penaltyBuilder.getResult() << std::endl;

    return 0;
}