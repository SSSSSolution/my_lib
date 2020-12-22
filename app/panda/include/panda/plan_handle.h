#ifndef REALITY_PLAN_HANDLE_H
#define REALITY_PLAN_HANDLE_H
#include <string>

namespace reality
{
    class PlanHandle
    {
    public:
        PlanHandle();
        void open_today_plan();

    private:
        void parse_config();
        void init_plan_file_list();
        void before_edit_plan();
        void finish_edit_plan();

        std::string m_panda_dir;
        std::string m_editor;
        std::string m_today_plan_dir;
        std::string m_today_plan_file;
    };
}

#endif
