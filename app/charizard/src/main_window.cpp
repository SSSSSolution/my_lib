#include "main_window.h"

#include <QApplication>
#include <QScreen>
#include <QHBoxLayout>

namespace reality
{
    namespace charizard
    {
        MainWindow::MainWindow() : QMainWindow(nullptr)
        {
            auto pos = QCursor::pos();
            auto screen = QApplication::screenAt(pos);

            int width = static_cast<int>(screen->geometry().width() * 2.0 / 4.0);
            int height = static_cast<int>(screen->geometry().height() * 2.0 / 4.0);
            int top = screen->geometry().top() +
                    (screen->geometry().height() - height)/2;
            int left = screen->geometry().left() +
                    (screen->geometry().width() - width)/2;
            setGeometry(left, top, width, height);

            m_handle = new RenderHandle(this);

            QWidget *center_widget = new QWidget(this);
            m_render_widget = new RenderWidget(m_handle, center_widget);
            m_control_bar_widget = new ControlBarWidget(m_handle, center_widget);

            QHBoxLayout *main_layout = new QHBoxLayout(center_widget);
            main_layout->setMargin(5);
            main_layout->addWidget(m_render_widget);
            main_layout->addWidget(m_control_bar_widget);
            main_layout->setAlignment(m_render_widget, Qt::AlignCenter);
            main_layout->setAlignment(m_control_bar_widget, Qt::AlignCenter);

            m_control_bar_widget->setMinimumWidth(200);

            setCentralWidget(center_widget);


        }

        MainWindow::~MainWindow() = default;
    }
}
