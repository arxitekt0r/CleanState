#include <QApplication>
#include "core/ApplicationController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ApplicationController controller;
    controller.showMainWindow();

    return app.exec();
}
