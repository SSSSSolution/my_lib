#include "plan_handle.h"
#include "dir.h"
#include <unistd.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "json.hpp"
#include "util.h"
#include <fcntl.h>

using namespace reality::common;
namespace reality
{
    PlanHandle::PlanHandle()
    {

    }

    void PlanHandle::open_today_plan()
    {
        parse_config();
        init_plan_file_list();

        before_edit_plan();

        open_file_with_editor(m_today_plan_file, m_editor);

        finish_edit_plan();
    }

    void PlanHandle::parse_config()
    {
        std::string home_dir = get_home_dir();
        std::string config_path = home_dir.append("/.config/panda/config.json");

        nlohmann::json config;

        try {
            std::ifstream ifs(config_path);
            ifs >> config;
            m_panda_dir = config.at("plan").at("dir").get<std::string>();
            m_editor = config.at("plan").at("editor").get<std::string>();
        } catch (...) {
            printf("cannot parse panda config path\n");
            exit(1);
        }
    }

    void PlanHandle::init_plan_file_list()
    {
        if (m_panda_dir.empty())
        {
            printf("panda dir is empty!\n");
            exit(-1);
        }

        std::vector<std::string> plan_file_list;

        std::string plan_dir;
        plan_dir.append("/").append(m_panda_dir).append("/.plan");
        Dir dir(plan_dir);

        auto year_dirs = dir.sub_dirs();
        for (auto y_dir : year_dirs)
        {
            std::string d;
            d.append(plan_dir).append("/").append(y_dir);
            Dir dir(d);

            auto mon_dirs = dir.sub_dirs();
            for (auto m_dir : mon_dirs)
            {
                std::string d;
                d.append(plan_dir).append("/").append(y_dir).append("/").append(m_dir);
                Dir dir(d);

                auto file_plans = dir.sub_files();
                for (auto f : file_plans)
                {
                    plan_file_list.push_back(f);
                }
            }
        }

        std::sort(plan_file_list.begin(), plan_file_list.end());
        for (auto f : plan_file_list)
        {
            printf("%s\n", f.c_str());
        }
    }

    void PlanHandle::before_edit_plan()
    {
        time_t rawtime;
        struct tm *time_info;

        time(&rawtime);
        time_info = localtime(&rawtime);

        int year = time_info->tm_year + 1900;
        int mon = time_info->tm_mon + 1;
        int day = time_info->tm_mday;

        std::string root_path;
        root_path.append(m_panda_dir).append("/.plan");
        m_today_plan_dir = get_dir_by_date(root_path, year, mon);
        m_today_plan_file = get_file_path_by_date(root_path, "plan", year, mon, day);

        if (access(m_today_plan_file.c_str(), F_OK) == -1)
        {
            std::string mkdir_cmd = std::string("mkdir -p ").append(m_today_plan_dir);
            system(mkdir_cmd.c_str());
        }
    }

    void PlanHandle::finish_edit_plan()
    {
        printf("enjoy your life :)\n");
    }
}
























