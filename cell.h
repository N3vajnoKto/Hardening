
#ifndef CELL_H
#define CELL_H

#include "items/itemgroup.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Cell : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Cell(ItemGroup* item = nullptr, QRectF sz  = {0, 0, 30, 30}, QObject *parent = nullptr);
    ~Cell();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF& box();
    ItemGroup* item();
    void setItem(ItemGroup* item);
    bool current() const;
    void setCurrent(bool st);


private:
    QRectF box_;
    ItemGroup* item_ = nullptr;
    bool current_ = false;

signals:

};

#endif // CELL_H
