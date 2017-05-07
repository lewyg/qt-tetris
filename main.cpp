#include "mainwindow.h"
#include <QtWidgets>

#include <stdlib.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    qsrand(QTime::currentTime().second());
    QApplication a(argc, argv);
    a.setApplicationName("Qt Tetris");
    a.setApplicationDisplayName("Qt Tetris");
    MainWindow w;
    w.setWindowTitle("Qt Tetris");
    w.show();

    return a.exec();
}
