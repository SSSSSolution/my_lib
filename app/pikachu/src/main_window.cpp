#include "main_window.h"

#include <thread>
#include <chrono>
#include <iostream>

#include <QApplication>
#include <QMenuBar>
#include <QScreen>
#include <QDebug>

namespace reality
{
    namespace pikachu
    {
        class MainWindowMenuBar : public QMenuBar
        {
        public:
            MainWindowMenuBar(QWidget *parent) : QMenuBar(parent)
            {
                addAction("File");
                addAction("Help");
            }
        };

        MainWindow::MainWindow() : QMainWindow()
        {
            move_to_center();
            setMenuBar(new MainWindowMenuBar(this));
        }

        void MainWindow::move_to_center()
        {
            auto primary_screen = QApplication::primaryScreen();
            int width = static_cast<int>(primary_screen->geometry().width() * 2.0 / 4.0);
            int height = static_cast<int>(primary_screen->geometry().height() * 2.0 / 4.0);
            int top = primary_screen->geometry().top() +
                    (primary_screen->geometry().height() - height)/2;
            int left = primary_screen->geometry().left() +
                    (primary_screen->geometry().width() - width)/2;
            setGeometry(left, top, width, height);
            qDebug() << "move to geometry: " << geometry();
        }


    }
}
