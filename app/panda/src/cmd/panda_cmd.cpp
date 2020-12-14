#include "panda_cmd.h"
#include <stdio.h>

namespace reality
{
    PandaCommand::PandaCommand():CommandProcessor("panda") {}

    void PandaCommand::print_helper()
    {
        fprintf(stdout, "Panda: a plan and note manager sofeware!\n"
                "usage: panda plan --> show plan of today.\n");
    }

    void PandaCommand::cmd_run()
    {
        return;
    }
}
