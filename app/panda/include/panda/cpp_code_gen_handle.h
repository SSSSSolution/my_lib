#ifndef REALITY_CPP_CODE_GEN_HANDLE_H
#define REALITY_CPP_CODE_GEN_HANDLE_H

#include <string>

namespace reality
{
    class CPPCodeGenHandle
    {
    public:
        CPPCodeGenHandle();
        void process();

    private:
        void parse_config();

        void before_edit();
        void end_edit();

    private:
        std::string m_editor;
        std::string m_cpp_template_dir;
    };
}

#endif
