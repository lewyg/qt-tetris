#ifndef CELL_H
#define CELL_H


#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QGradient>
#include <QDebug>
#include <consts.h>

class Cell : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    static const int size = BLOCK_SIZE;
public:
    Cell(int x = 0, int y = 0, QColor color = Qt::red, QObject *parent = 0);

    void setColor(QColor color);
    QColor getColor() const { return color; }

    void setPosition(int x, int y);

private:
    QColor color;
    QBrush brush;
    QPen pen;
    QRadialGradient gradient;
};

#endif // CELL_H
