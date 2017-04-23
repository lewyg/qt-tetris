#include "gameboard.h"

GameBoard::GameBoard(QObject * parent) : QGraphicsScene(parent)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            cells[i][j].setPosition(i, j);
            cells[i][j].setVisible(false);
            this->addItem(&cells[i][j]);
        }
    }

}
int xx = 0;
int yy = 0;
void GameBoard::showCell()
{
    cells[xx][yy].setVisible(true);
    cells[xx][yy].setColor(Qt::blue);
    xx += 1;
    if (xx == 10)
    {
        yy += 1;
        xx = 0;
    }


}
