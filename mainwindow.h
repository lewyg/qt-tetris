#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QShowEvent>
#include <QKeyEvent>
#include <QIcon>
#include <QDir>
#include <gameboard.h>
#include <cell.h>
#include <piece.h>
#include <consts.h>
#include <settingswindow.h>

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
    void startGame();
    void keyPressed(int key);
    void pauseGame();

public slots:
    void updateNextPiece(PieceShape shape);
    void updateLines(int lines);
    void updateLevel(int level);
    void updatePauseLabel();

private slots:
    void on_btStart_clicked();
    void on_btSettings_clicked();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    GameBoard *board;

    void fitSceneToView();
};

#endif // MAINWINDOW_H
