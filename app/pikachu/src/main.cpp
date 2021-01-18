#include <QApplication>
#include <memory>
#include <thread>
#include <chrono>
#include <string>

#include <QDir>
#include <QScreen>
#include <QDebug>

#include "main_window.h"
#include "preloading_widget.h"
#include "pikachu_app.h"
#include "conversion_handle.h"
#include "config.h"

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
    if (argc < 2)
    {
        printf("Usage: %s cfg_path\n", argv[0]);
        exit(-1);
    }
    Config::getInstance()->parse(argv[1]);
    QApplication app(argc, argv);

    QDir tmp_dir;
    if (!tmp_dir.exists("/tmp/pikachu"))
    {
        tmp_dir.mkpath("/tmp/pikachu");
    }
    if (!tmp_dir.exists("/tmp/pikachu/ascii_images"))
    {
        tmp_dir.mkpath("/tmp/pikachu/ascii_images");
    }

    auto window_geometry = caculate_window_geometry();

    std::string image_path = Config::getInstance()->data_dir();
    image_path.append("/pikachu.png");
    std::unique_ptr<PreloadingWindget> preloading_widget(new PreloadingWindget(image_path));
//    preloading_widget->setGeometry(window_geometry);
    preloading_widget->init();

    ConversionHandle handle(nullptr);
    MainWindow main_window(&handle);
    main_window.setGeometry(window_geometry);
    main_window.show();
    main_window.raise();

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










