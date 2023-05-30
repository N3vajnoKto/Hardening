
#include "itemgroup.h"

ItemGroup::ItemGroup(ItemBase* item, QObject* parent) : QObject(parent){
    item_ = item;
}

ItemGroup::ItemGroup(ItemGroup* ig) {
    item_ = ig->item();
    count_ = ig->count();
}

ItemGroup::~ItemGroup() {
    delete item_;
}

ItemBase* ItemGroup::item() const {
    return item_;
}

void ItemGroup::setItem(ItemBase* item) {
    item_ = item;
}

int ItemGroup::count() const {
    return count_;
}

void ItemGroup::setCount(int c) {
    count_ = c;
}

void ItemGroup::addCount(int c) {
    count_ += c;
}

int ItemGroup::maxNumber() const {
    return item()->maxNumber();
}

void ItemGroup::addItemGroup(ItemGroup* ig) {
    if (item()->id() == ig->item()->id()) {
        int extra = maxNumber() - count();
        extra = std::min(extra, ig->count());
        addCount(extra);
        ig->addCount(-extra);
    }
}

void ItemGroup::useItem(QPointF pnt) {
    item()->useItem(pnt);
    if (item()->isDisposable()) {
        addCount(-1);
    }
}

QPixmap ItemGroup::pixmap(int w, int h) const {
    return item()->pixmap(w, h, count());
}

bool ItemGroup::full() const {
    return (count() == maxNumber());
}
