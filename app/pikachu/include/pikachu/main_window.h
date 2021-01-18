#ifndef REALITY_PIKACHU_MAIN_WINDOW_H
#define REALITY_PIKACHU_MAIN_WINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QString>

#include "picture_widget.h"
#include "control_bar.h"
#include "conversion_handle.h"

namespace reality
{
namespace pikachu
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        MainWindow(ConversionHandle *handle);
        ~MainWindow();

    private:
        void move_to_center();
        void init_layout();

    private:
        QHBoxLayout *m_main_layout;

        PictureWidget *m_picture_widget;
        ControlBar *m_control_bar;

        ConversionHandle *m_handle;
    };
}
}

#endif
