#ifndef GAMEBOARD_H
#define GAMEBOARD_H


#include <QGraphicsScene>
#include <cell.h>


class GameBoard : public QGraphicsScene
{
    Q_OBJECT
public:
    GameBoard(QObject *parent = 0);

public slots:
    void showCell();

private:
    Cell cells[10][20];
};

#endif // GAMEBOARD_H
