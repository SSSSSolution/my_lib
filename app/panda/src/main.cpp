#include "rlog.h"
#include "panda_cmd.h"
#include "plan_cmd.h"

using namespace reality;
int main(int argc, char **argv)
{
    std::shared_ptr<PandaCommand> panda_cmd(new PandaCommand());
    std::shared_ptr<PlanCommand> plan_cmd(new PlanCommand());

    panda_cmd->add_sub_command(plan_cmd);
    panda_cmd->process(argc, argv);
}
