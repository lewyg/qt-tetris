#include "piece.h"

static const int coordsTable[7][4][2] = {
    { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
    { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
    { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
    { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
    { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
    { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
    { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
};

static const QColor colors[7] = {
    Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::gray, Qt::cyan, Qt::magenta
};

Piece::Piece(PieceShape shape)
{
    x = BLOCK_SIZE * (BOARD_WIDTH / 2);
    y = 0;

    for (int i = 0; i < 4; i++)
    {
        cells[i].setPosition(lx() + coordsTable[shape][i][0], ly() + coordsTable[shape][i][1]);
        cells[i].setVisible(true);
        cells[i].setColor(colors[shape]);
    }
}

void Piece::addX(int diff)
{
    x += diff;

    for (int i = 0; i < 4; i++)
    {
        cells[i].setX(cells[i].x() + diff);
    }
}

void Piece::addY(int diff)
{
    y += diff;

    for (int i = 0; i < 4; i++)
    {
        cells[i].setY(cells[i].y() + diff);
    }
}

void Piece::rotateLeft()
{
    for (int i = 0; i < 4; i++)
    {
        int xx = (cells[i].x() - x);
        int yy = (cells[i].y() - y);
        cells[i].setPos(x - yy, y + xx);
    }
}

void Piece::rotateRight()
{
    for (int i = 0; i < 4; i++)
    {
        int xx = (cells[i].x() - x);
        int yy = (cells[i].y() - y);
        cells[i].setPos(x - yy, y + xx);
    }
}
