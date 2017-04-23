#include "cell.h"

Cell::Cell(QObject *parent) : QObject(parent)
{
    setPosition(0, 0);
    this->setRect(x * size, y * size, size, size);
}

Cell::Cell(int x, int y, QColor color, QObject *parent) : QObject(parent)
{
    this->setRect(x * size, y * size, size, size);
    setPosition(x, y);
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
    this->x = x;
    this->y = y;
    setPos(x * size, y * size);
    qDebug() << "Cell::setposition(" << x << "," << y << ")";
}
