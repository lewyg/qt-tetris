#ifndef CELL_H
#define CELL_H


#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QGradient>
#include <QDebug>

class Cell : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    static const int size = 30;
public:
    Cell(QObject *parent = 0);
    Cell(int x, int y, QColor color = Qt::red, QObject *parent = 0);

    void setColor(QColor color);
    QColor getColor() const { return color; }

    int getX() const { return x; }
    int getY() const { return y; }

    void setPosition(int x, int y);

private:
    int x;
    int y;
    QColor color;
    QBrush brush;
    QPen pen;
    QRadialGradient gradient;
};

#endif // CELL_H
