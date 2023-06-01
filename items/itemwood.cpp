
#include "itemwood.h"

ItemWood::ItemWood(QObject* parent) : Item(parent)
{
    setAutouse(true);
    setDisposable(true);
    QPixmap pm;
    QPixmapCache::find("wood", &pm);
    setIcon(QIcon(pm));
    setId("wood");
}

ItemWood::ItemWood(const ItemWood* parent) : Item(parent) {

}
ItemBase* ItemWood::copy() const {
    return new ItemWood(this);
}

