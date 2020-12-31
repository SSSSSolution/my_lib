#ifndef REALITY_CPP_CODE_GEN_HANDLE_H
#define REALITY_CPP_CODE_GEN_HANDLE_H

#include <string>
#include <memory>

namespace reality
{
    struct CPPCodeInfo;
    class CPPCodeGenHandle
    {
    public:
        CPPCodeGenHandle();
        void process();

    private:
        void parse_config();

        void before_edit();
        void end_edit();
        void parse_edit_config();
        void gen_file();
        void gen_header_file();

    private:
        std::string m_editor{};
        std::string m_cpp_template_dir{};
        std::string m_edit_file{};
        std::string m_tmp_edit_file{};
        std::shared_ptr<CPPCodeInfo> m_code_info;
    };
}

#endif
