#include "rlog.h"
#include "panda_cmd.h"
#include "plan_cmd.h"
#include "code_gen_cmd.h"

using namespace reality;
int main(int argc, char **argv)
{
    std::shared_ptr<PandaCommand> panda_cmd(new PandaCommand());
    std::shared_ptr<PlanCommand> plan_cmd(new PlanCommand());
    std::shared_ptr<CodeGenCommand> code_gen_cmd(new CodeGenCommand());

    panda_cmd->add_sub_command(plan_cmd);
    panda_cmd->add_sub_command(code_gen_cmd);
    panda_cmd->process(argc, argv);
}
