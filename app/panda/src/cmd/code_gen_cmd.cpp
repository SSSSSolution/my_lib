#include "code_gen_cmd.h"
#include <stdio.h>
#include "cpp_code_gen_handle.h"
namespace reality
{
CodeGenCommand::CodeGenCommand() : CommandProcessor ("codegen") {}

    void CodeGenCommand::print_helper()
    {
        fprintf(stdout, "Usage: \n"
                "panda codegen cpp\n");
    }

    void CodeGenCommand::cmd_run()
    {
        std::string arg = next_arg(std::string("codegen"));
        if (arg == "cpp")
        {
            CPPCodeGenHandle handle;
            handle.process();
        } else {
            print_helper();
        }
    }

}
