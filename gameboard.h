#ifndef GAMEBOARD_H
#define GAMEBOARD_H


#include <QGraphicsScene>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <cell.h>
#include <piece.h>
#include <consts.h>


class GameBoard : public QGraphicsScene
{
    Q_OBJECT
public:
    GameBoard(QObject *parent = 0);
    int *shapeProbabilities;
    bool paused;

signals:
    void updateNextPiece(PieceShape shape);
    void updateLines(int lines);
    void updateLevel(int level);
    void updatePauseLabel();

public slots:
    void startGame();
    void keyPressed(int key);
    void setShapeProbabilities(int *probabilities);
    void pauseGame();

private slots:
    void updateAnimation();

private:
    Cell boardCells[BOARD_WIDTH][BOARD_HEIGHT];
    Piece *currentPiece;
    PieceShape nextShape;
    QTimeLine *timeLine;

    PieceShape getRandomShape();

    bool gameOver;

    int removedLines;
    int level;

    void moveLeft();
    void moveRight();

    bool moveDown();
    void fallDown();

    void rotateLeft();
    void rotateRight();

    bool canMoveCell(int x, int y);

    void startNextPiece();

    void runAnimation();
    void stopAnimation();

    void clearBoard();
    void restartGame();

    void removeLine(int line);
    void checkLines();

    void checkLevel();

    void checkGameOver();
};

#endif // GAMEBOARD_H
