#include "plan_handle.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "json.hpp"

namespace reality
{
    static std::string get_home_dir()
    {
        struct passwd *pw = getpwuid(getuid());
        const char *home_dir = pw->pw_dir;
        return std::string(home_dir);
    }

    PlanHandle::PlanHandle()
    {

    }

    void PlanHandle::open_today_plan()
    {
        parse_config();

        time_t rawtime;
        struct tm *time_info;

        time(&rawtime);
        time_info = localtime(&rawtime);

        std::string year = std::to_string(time_info->tm_year + 1900);
        std::string month = std::to_string(time_info->tm_mon + 1);
        if (std::stoi(month) < 10)
        {
            month.insert(0, "0");
        }
        std::string day = std::to_string(time_info->tm_mday);
        if (std::stoi(day) < 10)
        {
            day.insert(0, "0");
        }

        std::string plan_file;
        plan_file = plan_file.append(year).append(month).append(day).append(".plan");

        std::string plan_dir_path;
        plan_dir_path = plan_dir_path.append(m_plan_dir).append("/.plan/").append(year).
                append("/").append(month);

        std::string mkdir_cmd = std::string("mkdir -p ").append(plan_dir_path);
        system(mkdir_cmd.c_str());
        std::string cmd;
        cmd = cmd.append(m_editor).append(" ").append(plan_dir_path).
                append("/").append(plan_file);
        auto ret = system(cmd.c_str());

        finish_edit_plan();
    }

    void PlanHandle::parse_config()
    {
        std::string home_dir = get_home_dir();
        std::string config_path = home_dir.append("/.panda_config");

        nlohmann::json config;

        try {
            std::ifstream ifs(config_path);
            ifs >> config;
            m_plan_dir = config.at("plan").at("dir").get<std::string>();
            m_editor = config.at("plan").at("editor").get<std::string>();
        } catch (...) {
            printf("cannot parse panda config path\n");
            exit(1);
        }
    }

    void PlanHandle::finish_edit_plan()
    {
        printf("Enjoy your lief :)\n");
    }
}
























