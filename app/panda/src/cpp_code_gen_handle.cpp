#include "cpp_code_gen_handle.h"
#include "util.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
namespace reality
{
    struct CPPClassInfo
    {
        std::string class_name;
        bool has_constructor;
        bool has_destructor;
        bool has_virtual_destructor;
        bool has_copy_constructor;
        bool has_assign;
        bool has_move_constructor;
        bool has_move_assign;
    };

    struct CPPCodeInfo
    {
        std::string dest_dir;
        std::string header_file_name;
        std::string cpp_file_name;
        std::vector<std::string> namespaces;
        std::vector<CPPClassInfo> classes;
    };

    CPPCodeGenHandle::CPPCodeGenHandle()
    {

    }

    void CPPCodeGenHandle::process()
    {
        parse_config();
        before_edit();
        printf("cpp code gen process \n");
        end_edit();
    }

    void CPPCodeGenHandle::parse_config()
    {
        std::string home_dir = get_home_dir();
        std::string config_path = home_dir.append("/.panda_config");

        nlohmann::json config;

        try {
            std::ifstream ifs(config_path);
            ifs >> config;
            m_cpp_template_dir = config.at("codegen").at("cpp").at("template_dir").get<std::string>();
            m_editor = config.at("general").at("editor");

        } catch(...)
        {
            printf("cannot parse panda config path\n");
            exit(1);
        }
    }

    void CPPCodeGenHandle::before_edit()
    {

    }

    void CPPCodeGenHandle::end_edit()
    {

    }
}
