#ifndef REALITY_COMMAND_PROCESSOR_H
#define REALITY_COMMAND_PROCESSOR_H

#include <memory>
#include <string>
#include <map>
#include <vector>

namespace reality
{
    class CommandProcessor
    {
    public:
        CommandProcessor(std::string cmd);
        virtual ~CommandProcessor();

        void process(int argc, char **argv);
        void add_sub_command(std::shared_ptr<CommandProcessor> cmd);

    protected:
        virtual void print_helper() = 0;
        virtual void cmd_run() = 0;

        bool has_arg(std::string arg);
        std::string next_arg(std::string arg);

    protected:
        std::string m_cmd_str;
        std::vector<std::shared_ptr<CommandProcessor>> m_sub_cmd_list;
        std::vector<std::string> m_arg_list;
    };
}

#endif
