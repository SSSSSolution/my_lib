#include <string.h>
#include <iostream>
#include "command_processor.h"

using namespace reality;
class PandaCmd : public CommandProcessor
{
public:
    PandaCmd(): CommandProcessor("panda") {}
protected:

    virtual void print_helper() override
    {
        std::cout << "usage: " << "" << " plan\n";
    }

    virtual void cmd_run() override
    {
        if (has_arg("-t") || has_arg("--test"))
        {
            std::cout << "run test command" << std::endl;
        }
    }

};

class PandaSubCmdPlan : public CommandProcessor
{
public:
    PandaSubCmdPlan(): CommandProcessor("plan") {}

protected:
    virtual void print_helper() override
    {
        std::cout << "usage: " << "panda plan -i" << std::endl;
    }

    virtual void cmd_run() override
    {
        if (has_arg("-i") || has_arg("--iiii"))
        {
            std::cout << "run panda iiii command" << std::endl;
        }
    }
};

int main(int argc, char *argv[])
{

    std::shared_ptr<PandaCmd> panda_cmd(new PandaCmd());
    std::shared_ptr<PandaSubCmdPlan> panda_plan_cmd(new PandaSubCmdPlan);

    panda_cmd->add_sub_command(panda_plan_cmd);
    panda_cmd->process(argc, argv);
}
