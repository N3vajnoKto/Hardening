
#ifndef CELL_H
#define CELL_H

#include "item.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Cell : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Cell(QRectF sz, QObject *parent = nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF& box();
    Item* item();
    void setItem(Item* item);
    bool current() const;
    void setCurrent(bool st);

private:
    QRectF box_;
    Item* item_;
    bool current_ = false;

signals:

};

#endif // CELL_H