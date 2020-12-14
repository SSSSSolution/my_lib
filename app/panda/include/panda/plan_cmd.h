#include "command_processor.h"

namespace reality
{
    class PlanCommand : public CommandProcessor
    {
    public:
        PlanCommand();

    protected:
        virtual void print_helper();
        virtual void cmd_run();
    };
}
