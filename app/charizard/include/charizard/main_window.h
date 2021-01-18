#ifndef REALITY_CHARIZARD_MAIN_WINDOW_h
#define REALITY_CHARIZARD_MAIN_WINDOW_h

#include "render_widget.h"
#include "control_bar_widget.h"
#include "render_handle.h"

#include <QMainWindow>

namespace reality
{
    namespace charizard
    {
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        MainWindow();
        ~MainWindow();

    private:
        RenderHandle *m_handle;

        RenderWidget *m_render_widget;
        ControlBarWidget *m_control_bar_widget;
    };
    }
}

#endif
