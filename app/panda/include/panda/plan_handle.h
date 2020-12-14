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
        void finish_edit_plan();

        std::string m_plan_dir;
        std::string m_editor;
    };
}

#endif
