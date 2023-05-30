
#include "item.h"

Item::Item(QObject *parent) : ItemBase(parent)
{

}

Item::Item(const Item *parent) : ItemBase(parent) {
    player_ = parent->player_;
}

ItemBase* Item::copy() const {
    return new Item(this);
}

Player* Item::player() {
    return player_;
}
void Item::setPlayer(Player* player) {
    player_ = player;
}

bool Item::useItem(QPointF pos) {
    return true;
}
