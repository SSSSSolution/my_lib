#include "main_window.h"

#include <thread>
#include <chrono>
#include <iostream>

#include <QApplication>
#include <QMenuBar>
#include <QScreen>
#include <QDebug>

#include "about_dialog.h"

namespace reality
{
    namespace pikachu
    {
        class MainWindowMenuBar : public QMenuBar
        {
        public:
            MainWindowMenuBar(QWidget *parent) : QMenuBar(parent)
            {
                QAction *file_action = new QAction("File", this);
                QAction *help_action = new QAction("Help", this);
//                addAction("File");
//                addAction("Help");

                QMenu *help_menu = new QMenu(this);
                QAction *about_action = new QAction("About", this);

                std::cout << "hahahah" << std::endl;
                auto c = connect(about_action, &QAction::triggered, this, [this](bool b){
                   AboutDialog about_dialog(this);
                   about_dialog.exec();
                });
//                assert(c != nullptr);
                help_action->setMenu(help_menu);
                help_menu->addAction(about_action);


                addAction(file_action);
                addAction(help_action);
            }
        };

        MainWindow::MainWindow(ConversionHandle *handle)
            : QMainWindow(),
              m_handle(handle)
        {
            move_to_center();
            setMenuBar(new MainWindowMenuBar(this));

            init_layout();
        }

        MainWindow::~MainWindow() = default;

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

            setMinimumSize(width, height);
            qDebug() << "move to geometry: " << geometry();
        }

        void MainWindow::init_layout()
        {
            QWidget *centerWidget = new QWidget(this);

            m_picture_widget = new PictureWidget(m_handle, centerWidget);
            m_control_bar = new ControlBar(m_handle, centerWidget);

            m_main_layout = new QHBoxLayout(centerWidget);
            m_main_layout->setMargin(5);
            m_main_layout->addWidget(m_picture_widget);
            m_main_layout->addWidget(m_control_bar);

            m_main_layout->setStretchFactor(m_picture_widget, 3);
            m_main_layout->setStretchFactor(m_control_bar, 1);

            setCentralWidget(centerWidget);
        }


    }
}






















