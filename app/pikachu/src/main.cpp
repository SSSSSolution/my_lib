#include <QApplication>
#include "main_window.h"

using namespace reality::pikachu;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow mian_window;
    mian_window.show();

    return app.exec();
}
