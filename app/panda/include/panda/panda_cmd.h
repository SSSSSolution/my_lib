#ifndef REALITY_PANDA_CMD_H
#define REALITY_PANDA_CMD_H

#include "command_processor.h"

namespace reality
{
    class PandaCommand : public CommandProcessor
    {
    public:
        PandaCommand();

    protected:
        virtual void print_helper();
        virtual void cmd_run();
    };
}


#endif
