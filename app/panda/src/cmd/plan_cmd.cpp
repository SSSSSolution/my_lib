#include "plan_cmd.h"
#include <stdio.h>
#include "plan_handle.h"

namespace reality
{
    PlanCommand::PlanCommand(): CommandProcessor("plan") {}

    void PlanCommand::print_helper()
    {
        fprintf(stdout, "Usage: \n");
    }

    void PlanCommand::cmd_run()
    {
        PlanHandle plan_handle;
        plan_handle.open_today_plan();
    }
}
