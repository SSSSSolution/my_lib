#ifndef REALITY_CODE_GEN_CMD_H
#define REALITY_CODE_GEN_CMD_H

#include "command_processor.h"

namespace reality
{
    class CodeGenCommand : public CommandProcessor
    {
    public:
        CodeGenCommand();

    protected:
        virtual void print_helper();
        virtual void cmd_run();
    };
}

#endif
