
#include "item.h"

Item::Item(QObject *parent, QIcon icon)
    : QObject{parent}
{
    count_ = 1;
    icon_ = icon;
    box_ = {0, 0, 30, 30};
}

Item::Item(Item *parent) {
    count_ = parent->count_;
    box_ = parent->box_;
    icon_ = parent->icon_;
    maxNumber_ = parent->maxNumber_;
    id_ = parent->id_;
}

int Item::count() const {
    return count_;
}

void Item::setCount(int x) {
    count_ = x;
}

QIcon Item::icon() const {
    return icon_;
}

void Item::setIcon(QIcon icon) {
    icon_ = icon;
}

int Item::maxNumber() {
    return maxNumber_;
}

void Item::setId(QString str) {
    id_ = str;
}

QString Item::id() {
    return id_;
}

void Item::addCount(int add) {
    count_ += add;
}

bool Item::full() const {
    return (count_ == maxNumber_);
}

void Item::addItem(Item* item) {
    if (id_ == item->id()) {
        int extra = maxNumber() - count();
        extra = std::min(extra, item->count());
        addCount(extra);
        item->addCount(-extra);
    }
}

QPixmap Item::pixmap(int w, int h) const {
    if (h < 0 || w < 0) {
        w = box_.width();
        h = box_.height();
    }
    QPixmap pix = icon().pixmap(w, h);
    QPainter painter(&pix);
    if (count() > 1) {
        painter.setFont(QFont("Arial", 10, 2));
        painter.setPen(QPen(Qt::black, 4));
        painter.drawText(0, h - 1, QString::number(count()));
    }
    painter.end();

    return pix;

}

bool Item::autouse() {
    return autouse_;
}
void Item::setAutouse(bool bl) {
    autouse_ = bl;
}

void Item::setMaxNumber(int mx) {
    maxNumber_ = mx;
}

bool Item::useItem(QPointF pos) {
    qDebug() << pos;
    addCount(-1);
    return true;
}

