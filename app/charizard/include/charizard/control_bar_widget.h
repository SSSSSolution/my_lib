#ifndef REALITY_CHARIZARD_CONTROL_BAR_WIDGET_H
#define REALITY_CHARIZARD_CONTROL_BAR_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>

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

    private slots:
        void on_mass_radio_btn_clicked(QAbstractButton *);

    signals:
        void test_native_widget();

    private:
        RenderHandle *m_handle;
        // for draw line
        QPushButton *m_draw_line_btn;
        QLabel *m_draw_line_start_label;
        QLabel *m_draw_line_end_label;
        QLineEdit *m_start_edit;
        QLineEdit *m_end_edit;

        // for draw trianle
        QPushButton *m_draw_triangle_btn;
        QLabel *m_A_point_label;
        QLabel *m_B_point_label;
        QLabel *m_C_point_label;
        QLineEdit *m_A_edit;
        QLineEdit *m_B_edit;
        QLineEdit *m_C_edit;
        QButtonGroup *m_mass_btns;
        QRadioButton *m_mass_1_btn;
        QRadioButton *m_mass_4_btn;
        QRadioButton *m_mass_16_btn;
        SampleCount m_sample = Sample_Count_1;

        // for draw cube
        QPushButton *m_draw_cube_btn;

        // run btn
        QPushButton *m_run_btn;

        // stop btn
        QPushButton *m_stop_btn;

        // test native widget btn
        QPushButton *m_test_native_btn;

        // for clear
        QPushButton *m_clear_btn;
    };
    }
}


#endif
