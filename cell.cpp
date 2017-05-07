#include "cell.h"

Cell::Cell(int x, int y, QColor color, QObject *parent) : QObject(parent)
{
    this->setPos(x * size, y * size);
    this->setRect(x, y, size, size);
    this->setColor(color);
}

void Cell::setColor(QColor color)
{
    this->color = color;
    brush = QBrush(color);
    this->setBrush(brush);
}

void Cell::setPosition(int x, int y)
{
    this->setPos(x * size, y * size);
}
