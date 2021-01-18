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
                m_handle->draw_line(QPoint(0, 0), QPoint(1, 1));
            });
            assert(c != nullptr);
        }
    }
}
