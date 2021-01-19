#ifndef REALITY_CHARIZARD_CONTROL_BAR_WIDGET_H
#define REALITY_CHARIZARD_CONTROL_BAR_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include "render_handle.h"

namespace reality
{
    namespace charizard
    {
    class ControlBarWidget : public QWidget
    {
        Q_OBJECT
    public:
        ControlBarWidget(RenderHandle *handle, QWidget *parent);

    private:
        RenderHandle *m_handle;
        // for draw line
        QPushButton *m_draw_line_btn;
        QLabel *m_draw_line_start_label;
        QLabel *m_draw_line_end_label;
        QLineEdit *m_start_edit;
        QLineEdit *m_end_edit;

        // for draw cube
        QPushButton *m_draw_cube_btn;
    };
    }
}


#endif
