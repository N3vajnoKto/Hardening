
#include "itemwood.h"

ItemWood::ItemWood(QObject* parent) : Item(parent)
{
    setAutouse(true);
    setDisposable(true);
    setIcon(QIcon(":/icons/wood.png"));
    setId("wood");
}

ItemWood::ItemWood(const ItemWood* parent) : Item(parent) {

}
ItemBase* ItemWood::copy() const {
    return new ItemWood(this);
}

