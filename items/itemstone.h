
#ifndef ITEMSTONE_H
#define ITEMSTONE_H


#include "item.h"

class ItemStone : public Item
{
public:
    ItemStone(QObject* parent = nullptr);
    ItemStone(const ItemStone* parent);
    ItemBase* copy() const override;
};


#endif // ITEMSTONE_H
