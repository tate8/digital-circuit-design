#include "mainwindow.h"
#include "mainwindow.h"
#include <QApplication>

/// \brief the execution point of the program
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
