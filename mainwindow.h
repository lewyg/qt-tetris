#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gameboard.h>
#include <cell.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void showCell();

private slots:
    void on_btStart_clicked();
    void on_btQuit_clicked();

private:
    Ui::MainWindow *ui;
    GameBoard *board;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
