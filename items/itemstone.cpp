
#include "itemstone.h"

ItemStone::ItemStone(QObject* parent) : Item(parent)
{
    setAutouse(true);
    setDisposable(true);
    setIcon(QIcon(":/icons/stone.png"));
    setId("stone");
}

ItemStone::ItemStone(const ItemStone* parent) : Item(parent) {

}
ItemBase* ItemStone::copy() const {
    return new ItemStone(this);
}
