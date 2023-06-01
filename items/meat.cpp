
#include "meat.h"

Meat::Meat(QObject* parent) : Item(parent) {
    setAutouse(false);
    setDisposable(true);
    QPixmap pm;
    QPixmapCache::find("meat", &pm);
    setIcon(QIcon(pm));
    setId("meat");
}

Meat::Meat(const Meat* parent) : Item(parent) {

}

ItemBase* Meat::copy() const {
    return new Meat(this);
}

