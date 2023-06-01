
#include "itemstone.h"

ItemStone::ItemStone(QObject* parent) : Item(parent)
{
    setAutouse(true);
    setDisposable(true);
    QPixmap pm;
    QPixmapCache::find("stone", &pm);
    setIcon(QIcon(pm));
    setId("stone");
}

ItemStone::ItemStone(const ItemStone* parent) : Item(parent) {

}
ItemBase* ItemStone::copy() const {
    return new ItemStone(this);
}
