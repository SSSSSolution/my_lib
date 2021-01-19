#include "control_bar_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace reality
{
    namespace charizard
    {
        ControlBarWidget::ControlBarWidget(RenderHandle *handle, QWidget *parent)
            : QWidget(parent), m_handle(handle)
        {
            m_draw_line_btn = new QPushButton("draw line");

            QHBoxLayout *draw_line_point_layout = new QHBoxLayout();
            m_start_edit = new QLineEdit("start point");
            m_end_edit = new QLineEdit("end point");
            draw_line_point_layout->addWidget(m_start_edit);
            draw_line_point_layout->addWidget(m_end_edit);

            auto main_layout = new QVBoxLayout(this);
            main_layout->addLayout(draw_line_point_layout);
            main_layout->addWidget(m_draw_line_btn);
            main_layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));



            auto c = connect(m_draw_line_btn, &QPushButton::clicked, this, [this](){
                bool succ = true;

                auto start = m_start_edit->text();
                QStringList str_list = start.split(",");
                assert(str_list.size() == 2);
                float start_x = str_list[0].toFloat(&succ);
                assert(succ);
                float start_y = str_list[0].toFloat(&succ);
                assert(succ);

                auto end = m_end_edit->text();
                str_list = end.split(",");
                float end_x = str_list[1].toFloat(&succ);
                assert(succ);
                float end_y = str_list[1].toFloat(&succ);
                assert(succ);
//                float start_x = 0.0f;
//                float start_y = 0.0f;
//                float end_x = 1.0f;
//                float end_y = 1.0f;
//                for (int i = 0; i < 10000; i++)
//                {
//                    start_x += 0.00001f;
                    m_handle->draw_line(QPointF(start_x, start_y), QPointF(end_x, end_y));
//                }
            });
            assert(c != nullptr);
        }
    }
}
