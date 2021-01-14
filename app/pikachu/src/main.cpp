#include <QApplication>
#include <memory>
#include <thread>
#include <chrono>

#include <QScreen>
#include <QDebug>

#include "main_window.h"
#include "preloading_widget.h"
#include "pikachu_app.h"

using namespace reality::pikachu;

static QRect caculate_window_geometry()
{
    auto pos = QCursor::pos();
    auto screen = QApplication::screenAt(pos);

    int width = static_cast<int>(screen->geometry().width() * 2.0 / 4.0);
    int height = static_cast<int>(screen->geometry().height() * 2.0 / 4.0);
    int top = screen->geometry().top() +
            (screen->geometry().height() - height)/2;
    int left = screen->geometry().left() +
            (screen->geometry().width() - width)/2;

    return QRect(left, top, width, height);
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    auto window_geometry = caculate_window_geometry();

    std::unique_ptr<PreloadingWindget> preloading_widget(new PreloadingWindget(&app));
    preloading_widget->setGeometry(window_geometry);
    preloading_widget->init();

    MainWindow main_window;
    main_window.setGeometry(preloading_widget->get_last_geometry());
    main_window.show();

    QTimer close_timer;
    bool close_me = false;
    close_timer.singleShot(300, [&close_me](){
        close_me = true;
    });

    while (!close_me)
    {
        QCoreApplication::processEvents();
    }

    preloading_widget->finish(&main_window);
    return app.exec();
}










