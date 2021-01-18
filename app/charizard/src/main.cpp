#include <QApplication>

#include "main_window.h"

using namespace reality::charizard;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow main_window;
    main_window.show();

    return app.exec();
}
