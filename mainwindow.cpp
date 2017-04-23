#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    board = new GameBoard();
    connect(this, SIGNAL(showCell()), board, SLOT(showCell()));

    ui->gvBoard->setRenderHint(QPainter::Antialiasing, true);

    board->setSceneRect(0, 0, 300, 540);
    ui->gvBoard->setScene(board);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btStart_clicked() {
    ui->btStart->setText("Dupa");
    emit showCell();
}

void MainWindow::on_btQuit_clicked() {
    close();
}
