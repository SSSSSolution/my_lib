#include "command_processor.h"
#include <string.h>
#include <algorithm>

namespace reality
{
    CommandProcessor::CommandProcessor(std::string cmd)
        : m_cmd_str(cmd)
    {

    }

    CommandProcessor::~CommandProcessor() = default;

    void CommandProcessor::process(int argc, char **argv)
    {
        if (argc <= 0)
            return;

        // first process sub cmd
        if (argc > 1)
        {
           for (auto sub_cmd : m_sub_cmd_list)
           {
                if (sub_cmd->m_cmd_str == argv[1])
                {
                    sub_cmd->process(argc-1, argv+1);
                    return;
                }
           }
        }

        // if no sub cmd is found, run this cmd.
        if (argc > 1)
        {
            if (strcmp(argv[1], "-h") == 0 ||
                strcmp(argv[1], "--help") == 0)
            {
                print_helper();
                return;
            }
        }

        for (int i = 0; i < argc; ++i)
        {
            m_arg_list.push_back(std::string(argv[i]));
        }
        cmd_run();
    }

    bool CommandProcessor::has_arg(std::string arg)
    {
        if (std::find(m_arg_list.begin(), m_arg_list.end(), arg) != m_arg_list.end())
        {
            return true;
        }
        return false;
    }

    std::string CommandProcessor::next_arg(std::string arg)
    {
        std::string next_arg;
        auto iter = std::find(m_arg_list.begin(), m_arg_list.end(), arg);
        if (iter != m_arg_list.end() && ++iter != m_arg_list.end())
        {
            next_arg = *iter;
        }

        return next_arg;
    }

    void CommandProcessor::add_sub_command(std::shared_ptr<CommandProcessor> cmd)
    {
        m_sub_cmd_list.push_back(cmd);
    }
}
