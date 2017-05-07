#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setFocusPolicy(Qt::StrongFocus);
    ui->lblPaused->setVisible(false);

    board = new GameBoard();

    connect(this, SIGNAL(startGame()), board, SLOT(startGame()));
    connect(this, SIGNAL(keyPressed(int)), board, SLOT(keyPressed(int)));
    connect(this, SIGNAL(pauseGame()), board, SLOT(pauseGame()));

    connect(board, SIGNAL(updateNextPiece(PieceShape)), this, SLOT(updateNextPiece(PieceShape)));
    connect(board, SIGNAL(updateLines(int)), this, SLOT(updateLines(int)));
    connect(board, SIGNAL(updateLevel(int)), this, SLOT(updateLevel(int)));
    connect(board, SIGNAL(updatePauseLabel()), this, SLOT(updatePauseLabel()));

    ui->gvNextPiece->setScene(new QGraphicsScene());

    ui->gvBoard->setRenderHint(QPainter::Antialiasing, true);
    ui->gvBoard->setScene(board);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateNextPiece(PieceShape shape)
{
    ui->gvNextPiece->scene()->clear();

    Piece nextPiece(shape);

    for (int i = 0; i < 4; i++)
    {
        ui->gvNextPiece->scene()->addItem(new Cell(nextPiece.cells[i].x() / BLOCK_SIZE,
                                                   nextPiece.cells[i].y() / BLOCK_SIZE,
                                                   nextPiece.cells[i].getColor()));
    }
}

void MainWindow::updateLines(int lines)
{
    ui->lcdLines->display(lines);
}

void MainWindow::updateLevel(int level)
{
    ui->lcdLevel->display(level);
}

void MainWindow::updatePauseLabel()
{
    ui->lblPaused->setVisible(!ui->lblPaused->isVisible());
}

void MainWindow::on_btStart_clicked() {
    ui->btStart->setText("Restart");
    emit startGame();
}

void MainWindow::on_btSettings_clicked() {
    SettingsWindow *settings = new SettingsWindow(board->shapeProbabilities);

    connect(settings, SIGNAL(setShapeProbabilities(int *)), board, SLOT(setShapeProbabilities(int*)));
    connect(settings, SIGNAL(pauseGame()), board, SLOT(pauseGame()));

    settings->setWindowFlags(Qt::Window| Qt::WindowTitleHint);

    if (!board->paused)
        emit pauseGame();

    settings->show();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    ui->gvBoard->fitInView(board->sceneRect());
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    ui->gvBoard->fitInView(board->sceneRect());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Space:
            emit keyPressed(event->key());
            break;
        case Qt::Key_P:
            emit pauseGame();
            break;
        case Qt::Key_Escape:
            close();
            break;
    }
}
