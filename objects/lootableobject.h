
#ifndef LOOTABLEOBJECT_H
#define LOOTABLEOBJECT_H


#include "object.h"
#include "../items/item.h"
#include <random>

class SpawnOption {
public:
    SpawnOption(Item* item, int mn, int mx, double chance = 1);
    int minimum();
    int maximum();
    Item* item();
    double chance();
    ItemGroup* spawn();
private:
    Item* item_ = nullptr;
    int minimum_ = 0;
    int maximum_ = 0;
    double chance_ = 1;

};

class LootableObject : public Object
{
public:
    LootableObject(QObject* parent = nullptr);
    ~LootableObject();
    std::vector<SpawnOption>& loot();
    virtual void die() override;
private:
    std::vector<SpawnOption> loot_;

};

#endif // LOOTABLEOBJECT_H
