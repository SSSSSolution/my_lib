#include "cpp_code_gen_handle.h"
#include "util.h"
#include "json.hpp"
#include "file.h"
#include <iostream>
#include <fstream>
using namespace reality::common;
namespace reality
{
    struct CPPClassInfo
    {
        std::string class_name;
        bool has_constructor{false};
        bool has_destructor{false};
        bool has_virtual_destructor{false};
        bool has_copy_constructor{false};
        bool has_assign{false};
        bool has_move_constructor{false};
        bool has_move_assign{false};
    };

    struct CPPCodeInfo
    {
        std::string dest_dir;
        std::string header_file_name;
        std::string cpp_file_name;
//        std::vector<std::string> namespaces;
        std::map<std::vector<std::string>, std::vector<CPPClassInfo>> classes;
    };

    CPPCodeGenHandle::CPPCodeGenHandle()
    {
        std::string home_dir = get_home_dir();
        m_edit_file = home_dir.append("/.config/panda/codegen/cpp/config.json");
        m_code_info = std::make_shared<CPPCodeInfo>();
    }

    void CPPCodeGenHandle::process()
    {
        parse_config();
        before_edit();
        open_file_with_editor(m_tmp_edit_file, m_editor);
        end_edit();
    }

    void CPPCodeGenHandle::parse_config()
    {
        std::string home_dir = get_home_dir();
        std::string config_path;
        config_path.append(home_dir).append("/.config/panda/config.json");
        m_cpp_template_dir.append(home_dir).append("/.config/panda/codegen/cpp/template");
        nlohmann::json config;

        try {
            std::ifstream ifs(config_path);
            ifs >> config;
            m_editor = config.at("general").at("editor");

        } catch(...)
        {
            printf("cannot parse panda config path\n");
            exit(1);
        }
    }

    void CPPCodeGenHandle::before_edit()
    {
        m_tmp_edit_file.append(m_edit_file).append(".tmp");

        File f(m_edit_file);
        f.copy(m_tmp_edit_file);
    }

    void CPPCodeGenHandle::end_edit()
    {
        parse_edit_config();
        gen_file();
    }

    static void print_cpp_code_info(std::shared_ptr<CPPCodeInfo> cpp_info)
    {
        printf("dest_dir: %s\n", cpp_info->dest_dir.c_str());
        printf("header file: %s\n", cpp_info->header_file_name.c_str());
        printf("cpp file: %s\n", cpp_info->cpp_file_name.c_str());
        for (auto c : cpp_info->classes)
        {
            printf("namespace: \n    ");
            const auto &namespaces = c.first;
            for (auto n : namespaces)
            {
                printf("%s::", n.c_str());
            }
            printf("\n");
            const auto &classes = c.second;
            for (auto c : classes)
            {
                printf("    class name: %s\n", c.class_name.c_str());
                printf("    c:%d, cc:%d, mc:%d, d:%d, vd:%d, a:%d, ma:%d\n",
                       c.has_constructor, c.has_copy_constructor, c.has_move_constructor,
                       c.has_destructor, c.has_virtual_destructor, c.has_assign, c.has_move_assign);
            }
        }
    }

    void CPPCodeGenHandle::parse_edit_config()
    {
        File f(m_tmp_edit_file);
        f.sync();

        nlohmann::json config;
        try {
            std::ifstream ifs(f.absolute_path());
            ifs >> config;
            m_code_info->dest_dir = config.at("dest_dir").get<std::string>();
            auto filename = config.at("filename").at("name").get<std::string>();
            auto suffix = config.at("filename").at("suffix").get<std::string>();
            // hh hpp h
            if(suffix.find("hh") != suffix.npos)
            {
                m_code_info->header_file_name.append(filename).append(".hh");
            } else if (suffix.find("hpp") != suffix.npos)
            {
                m_code_info->header_file_name.append(filename).append(".hpp");
            } else if (suffix.find("h") != suffix.npos)
            {
                m_code_info->header_file_name.append(filename).append(".h");
            }
            // cc cpp c
            if(suffix.find("cc") != suffix.npos)
            {
                m_code_info->cpp_file_name.append(filename).append(".cc");
            } else if (suffix.find("cpp") != suffix.npos)
            {
                m_code_info->cpp_file_name.append(filename).append(".cpp");
            } else if (suffix.find("c") != suffix.npos)
            {
                m_code_info->cpp_file_name.append(filename).append(".c");
            }

            for (int i = 1; ; i++)
            {
                auto ns = std::string("namespace_").append(std::to_string(i));
                if (config.find(ns.c_str()) == config.end())
                {
                    break;
                }
                auto nss = config.at(ns.c_str()).at("name").get<std::string>();

                std::vector<std::string> namespaces;
                while(nss.find("::") != nss.npos)
                {
                    auto n = nss.substr(0, nss.find("::"));
                    nss.erase(0, nss.find("::")+2);
                    namespaces.push_back(n);
                }
                if (!nss.empty())
                {
                    namespaces.push_back(nss);
                }

                std::vector<CPPClassInfo> class_infos;
                for (int j = 1; ; j++)
                {
                    auto cl = std::string("class_").append(std::to_string(j));
                    if (config.at(ns.c_str()).find(cl.c_str()) == config.at(ns.c_str()).end())
                    {
                        break;
                    }
                    CPPClassInfo class_info;
                    class_info.class_name = config.at(ns.c_str()).at(cl.c_str()).at("name").get<std::string>();

                    auto func_str = config.at(ns.c_str()).at(cl.c_str()).
                            at("default_funcs").get<std::string>();
                    auto funcs = split_str(func_str, "/");
                    if (std::find(funcs.begin(), funcs.end(), "c") != funcs.end())
                    {
                        class_info.has_constructor = true;
                    }
                    if (std::find(funcs.begin(), funcs.end(), "cc") != funcs.end())
                    {
                        class_info.has_copy_constructor = true;
                    }
                    if (std::find(funcs.begin(), funcs.end(), "mc") != funcs.end())
                    {
                        class_info.has_move_constructor = true;
                    }
                    if (std::find(funcs.begin(), funcs.end(), "d") != funcs.end())
                    {
                        class_info.has_destructor = true;
                    }
                    if (std::find(funcs.begin(), funcs.end(), "vd") != funcs.end())
                    {
                        class_info.has_virtual_destructor = true;
                    }
                    if (std::find(funcs.begin(), funcs.end(), "a") != funcs.end())
                    {
                        class_info.has_assign = true;
                    }
                    if (std::find(funcs.begin(), funcs.end(), "ma") != funcs.end())
                    {
                        class_info.has_move_assign = true;
                    }

                    class_infos.push_back(class_info);
                }
                m_code_info->classes[namespaces] = class_infos;
            }
        } catch(nlohmann::detail::exception& e)
        {
            printf("json throw an error: %s, try to fix.\n", e.what());
            printf("cannot parse panda cpp code gen config file\n");
            exit(1);
        }

        f.copy(m_edit_file);
        f.remove();

        print_cpp_code_info(m_code_info);
    }

    void CPPCodeGenHandle::gen_file()
    {
        // gen header
        if (!m_code_info->header_file_name.empty())
        {
            gen_header_file();
        }
    }

    void CPPCodeGenHandle::gen_header_file()
    {
        File f(m_code_info->header_file_name);
        if (f.exist())
        {
            char input[128] = {};
            printf("header file %s already exist, are you want rewrite it?(yes/no): ", f.absolute_path().c_str());
            scanf("%s", input);
        }

        std::string head_temp;
        File t(head_temp.append(m_cpp_template_dir).append("/foo.h"));
        if(!t.exist())
        {
            printf("Error: template file %s is not exist!!!\n", head_temp.c_str());
        }
//        f.save();
    }
}





















