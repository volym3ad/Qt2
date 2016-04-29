#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setMaximumWidth(700);
    mainWindow.setWindowTitle("THE_LATEST_NEWS");
    mainWindow.setStyleSheet("background-color: lightyellow");
    mainWindow.show();

    return app.exec();
}


