
#include "itembase.h"

ItemBase::ItemBase(QObject *parent, const QIcon& icon)
    : QObject{parent}
{
    icon_ = icon;
    box_ = {0, 0, 30, 30};
}

ItemBase::ItemBase(QObject *parent) {
    QPixmap pm;
    QPixmapCache::find("notImpl", &pm);
    icon_ = QIcon(pm);
}


ItemBase::ItemBase(const ItemBase *parent) {
    box_ = parent->box_;
    icon_ = parent->icon_;
    id_ = parent->id_;
    autouse_ = parent->autouse_;
    disposable_ = parent->disposable_;
    maxNumber_ = parent->maxNumber_;
}

ItemBase::~ItemBase() {
    emit itemDestroyed(this);
}

ItemBase* ItemBase::copy() const {
    return new ItemBase(this);
}


QIcon ItemBase::icon() const {
    return icon_;
}

void ItemBase::setIcon(const QIcon& icon) {
    icon_ = icon;
}

void ItemBase::setId(QString str) {
    id_ = str;
}

QString ItemBase::id() {
    return id_;
}

QPixmap ItemBase::pixmap(int w, int h, int cnt) const {
    if (h < 0 || w < 0) {
        w = box_.width();
        h = box_.height();
    }
    QPixmap pix = icon_.pixmap(w, h);
    QPainter painter(&pix);
    if (cnt > 1) {
        painter.setFont(QFont("Arial", 10, 2));
        painter.setPen(QPen(Qt::black, 4));
        painter.drawText(0, h - 1, QString::number(cnt));
    }
    painter.end();

    return pix;

}

int ItemBase::maxNumber() const {
    return maxNumber_;
}
void ItemBase::setMaxNumber(int mx) {
    maxNumber_ = mx;
}

bool ItemBase::autouse() {
    return autouse_;
}
void ItemBase::setAutouse(bool bl) {
    autouse_ = bl;
}


bool ItemBase::useItem(QPointF pos) {
    return true;
}

bool ItemBase::isDisposable() const {
    return disposable_;
}

void ItemBase::setDisposable(bool bl) {
    disposable_ = bl;
}

