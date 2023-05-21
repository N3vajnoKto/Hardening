
#include "cell.h"

Cell::Cell(QRectF sz, QObject *parent)
    : QObject{parent}, QGraphicsItem()
{
    box_ = sz;
}

QRectF& Cell::box() {
    return box_;
}

QRectF Cell::boundingRect() const {
    return box_;
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->save();
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (current()) {
        painter->setBrush(QColor(250, 250, 0, 200));
    } else {
        painter->setBrush(QColor(250, 250, 250, 200));
    }
    painter->drawRect(box());

    painter->restore();
}

Item* Cell::item() {
    return item_;
}

void Cell::setItem(Item* item) {
    item_ = item;
}

bool Cell::current() const {
    return current_;
}
void Cell::setCurrent(bool st) {
    current_ = st;
}
