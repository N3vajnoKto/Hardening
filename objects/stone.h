
#ifndef STONE_H
#define STONE_H



#include "lootableobject.h"
#include "../items/itemstone.h"


class Stone : public LootableObject
{
public:
    Stone(QObject* parent = nullptr);
    void getDamage(Damage damage) override;
};

#endif // STONE_H
