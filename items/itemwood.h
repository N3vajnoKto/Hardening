
#ifndef ITEMWOOD_H
#define ITEMWOOD_H


#include "item.h"

class ItemWood : public Item
{
public:
    ItemWood(QObject* parent = nullptr);
    ItemWood(const ItemWood* parent);
    ItemBase* copy() const override;
};

#endif // ITEMWOOD_H
