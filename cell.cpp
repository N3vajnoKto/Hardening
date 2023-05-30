
#include "cell.h"

Cell::Cell(ItemGroup* item, QRectF sz, QObject *parent)
    : QObject{parent}, QGraphicsItem(), item_(item)
{
    box_ = sz;
}

Cell::~Cell() {
    delete item_;
}

QRectF& Cell::box() {
    return box_;
}

QRectF Cell::boundingRect() const {
    return QRectF(box_.x() - 2, box_.y() - 2, box_.width() + 5, box_.height() + 5);
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

    if (item() != nullptr) {
        int width = box().width() - 3;
        int height = box().height() - 3;
        painter->drawPixmap(1, 1, item()->pixmap(width, height));
    }

    painter->restore();
}

ItemGroup* Cell::item() {
    return item_;
}

void Cell::setItem(ItemGroup* item) {
    item_ = item;
}

bool Cell::current() const {
    return current_;
}
void Cell::setCurrent(bool st) {
    current_ = st;
}
