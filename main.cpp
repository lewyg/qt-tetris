#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Qt Tetris");
    a.setApplicationDisplayName("Qt Tetris");
    MainWindow w;
    w.setWindowTitle("Qt Tetris");
    w.show();

    return a.exec();
}
