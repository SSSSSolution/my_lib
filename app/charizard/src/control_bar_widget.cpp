#include "control_bar_widget.h"
#include "rlog.h"
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
            m_draw_triangle_btn = new QPushButton("draw triangle");
            m_draw_cube_btn = new QPushButton("draw cube");
            m_clear_btn = new QPushButton("clear");
            m_run_btn = new QPushButton("run");
            m_stop_btn = new QPushButton("stop");
            m_test_native_btn = new QPushButton("test native widget");

            QHBoxLayout *draw_line_point_layout = new QHBoxLayout();
            m_start_edit = new QLineEdit("start point");
            m_end_edit = new QLineEdit("end point");
            draw_line_point_layout->addWidget(m_start_edit);
            draw_line_point_layout->addWidget(m_end_edit);

            QHBoxLayout *draw_triangle_layout = new QHBoxLayout();
            m_A_point_label = new QLabel("A");
            m_B_point_label = new QLabel("B");
            m_C_point_label = new QLabel("C");
            m_A_edit = new QLineEdit();
            m_B_edit = new QLineEdit();
            m_C_edit = new QLineEdit();
            draw_triangle_layout->addWidget(m_A_point_label);
            draw_triangle_layout->addWidget(m_A_edit);
            draw_triangle_layout->addWidget(m_B_point_label);
            draw_triangle_layout->addWidget(m_B_edit);
            draw_triangle_layout->addWidget(m_C_point_label);
            draw_triangle_layout->addWidget(m_C_edit);

            QHBoxLayout *mass_btns_layout = new QHBoxLayout();
            m_mass_1_btn = new QRadioButton("mass_1");
            m_mass_4_btn = new QRadioButton("mass_4");
            m_mass_16_btn = new QRadioButton("mass_16");
            mass_btns_layout->addWidget(m_mass_1_btn);
            mass_btns_layout->addWidget(m_mass_4_btn);
            mass_btns_layout->addWidget(m_mass_16_btn);
            m_mass_btns = new QButtonGroup();
            m_mass_btns->setExclusive(true);
            m_mass_btns->addButton(m_mass_1_btn);
            m_mass_btns->addButton(m_mass_4_btn);
            m_mass_btns->addButton(m_mass_16_btn);
            m_mass_1_btn->setChecked(true);

            auto main_layout = new QVBoxLayout(this);
            main_layout->setMargin(5);
            main_layout->addLayout(draw_line_point_layout);
            main_layout->addWidget(m_draw_line_btn);
            main_layout->addLayout(draw_triangle_layout);
            main_layout->addWidget(m_draw_triangle_btn);
            main_layout->addLayout(mass_btns_layout);
            main_layout->addWidget(m_draw_cube_btn);
            main_layout->addSpacerItem(new QSpacerItem(1, 100, QSizePolicy::Expanding, QSizePolicy::Expanding));
            main_layout->addWidget(m_run_btn);
            main_layout->addWidget(m_stop_btn);
            main_layout->addWidget(m_test_native_btn);
            main_layout->addWidget(m_clear_btn);


            auto c = connect(m_draw_line_btn, &QPushButton::clicked, this, [this](){
                bool succ = true;

                auto start = m_start_edit->text();
                QStringList str_list = start.split(",");
                assert(str_list.size() == 2);
                float start_x = str_list[0].toFloat(&succ);
                assert(succ);
                float start_y = str_list[1].toFloat(&succ);
                assert(succ);

                auto end = m_end_edit->text();
                str_list = end.split(",");
                float end_x = str_list[0].toFloat(&succ);
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
                std::cout << "start_x: " << start_x << " start_y: " << start_y
                          << "end_x: " << end_x << " end_y: " <<end_y  << std::endl;
                    m_handle->draw_line(QPointF(start_x, start_y), QPointF(end_x, end_y));
//                }
            });
            assert(c != nullptr);

            c = connect(m_draw_cube_btn, &QPushButton::clicked, this, [this](){
               RLOG(WARN, "draw_cube has not implementate");
            });
            assert(c != nullptr);

            c = connect(m_mass_btns, SIGNAL(buttonClicked(QAbstractButton *)),
                        this, SLOT(on_mass_radio_btn_clicked(QAbstractButton *)));
            assert(c != nullptr);

            c = connect(m_draw_triangle_btn, &QPushButton::clicked, this, [this](){
                bool succ;

                auto strs = m_A_edit->text();
                QStringList str_list = strs.split(",");
                float A_x = str_list[0].toFloat(&succ);
                if (!succ)
                {
                    A_x = 0.0f;
                }
                float A_y = str_list[1].toFloat(&succ);
                if (!succ)
                {
                    A_y = 0.0f;
                }

                strs = m_B_edit->text();
                str_list = strs.split(",");
                float B_x = str_list[0].toFloat(&succ);
                if (!succ)
                {
                    B_x = 1.0f;
                }
                float B_y = str_list[1].toFloat(&succ);
                if (!succ)
                {
                    B_y = 1.0f;
                }

                strs = m_C_edit->text();
                str_list = strs.split(",");
                float C_x = str_list[0].toFloat(&succ);
                if (!succ)
                {
                    C_x = 1.0f;
                }
                float C_y = str_list[1].toFloat(&succ);
                if (!succ)
                {
                    C_y = 0.0f;
                }

                m_handle->draw_triangle_(QPointF(A_x, A_y), QPointF(B_x, B_y), QPointF(C_x, C_y), m_sample);
            });
            assert(c != nullptr);

            c = connect(m_run_btn, &QPushButton::clicked, this, [this](){
                m_handle->run();
            });
            assert(c != nullptr);

            c = connect(m_stop_btn, &QPushButton::clicked, this, [this](){
                m_handle->stop();
            });
            assert(c != nullptr);

            c = connect(m_test_native_btn, &QPushButton::clicked, this, [this](){

            });
            assert(c != nullptr);

             c = connect(m_clear_btn, &QPushButton::clicked, this, [this](){
                m_handle->clear();
             });
             assert(c != nullptr);

        }

        void ControlBarWidget::on_mass_radio_btn_clicked(QAbstractButton *)
        {
            QList<QAbstractButton*> btn_list = m_mass_btns->buttons();
            for (auto btn : btn_list)
            {
                QString strStatus = btn->isChecked() ? "Checked" : "Unchecked";
                if (btn->isChecked())
                {
                    if (btn->text() == "mass_1")
                    {
                        m_sample = Sample_Count_1;
                    } else if (btn->text() == "mass_4")
                    {
                        m_sample = Sample_Count_4;
                    } else {
                        m_sample = Sample_Count_16;
                    }
                }
            }
        }
    }
}






















