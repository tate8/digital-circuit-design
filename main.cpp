#include "mainwindow.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFile>

/// \brief the execution point of the program
int main(int argc, char *argv[])
{
    //create the application and the main window
    QApplication app(argc, argv);
    MainWindow w;

    //open qss file
    QFile file(":/styles/styles.qss");

    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "Failed to open styles.qss";
        return -1;  // Exit if the stylesheet cannot be opened
    }

    QString styleSheet { QString(file.readAll()) };

    //setup stylesheet
    app.setStyleSheet(styleSheet);

    //run
    w.show();
    file.close();
    return app.exec();
}
