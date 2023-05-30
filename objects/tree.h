
#ifndef TREE_H
#define TREE_H

#include "lootableobject.h"
#include "../items/itemwood.h"


class Tree : public LootableObject
{
public:
    Tree(QObject* parent = nullptr);
    void getDamage(Damage damage) override;
};

#endif // TREE_H
