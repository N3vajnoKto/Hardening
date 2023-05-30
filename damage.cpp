
#include "damage.h"

Damage::Damage(int axe, int pickaxe, int sword)
{
    axeDamage_ = axe;
    swordDamage_ = sword;
    pickaxeDamage_ = pickaxe;
}

double Damage::axeDamage() {
    return axeDamage_;
}
void Damage::setAxeDamage(double damage) {
    axeDamage_ = damage;
}

double Damage::pickaxeDamage() {
    return pickaxeDamage_;
}

void Damage::setPickaxeDamage(double damage) {
    pickaxeDamage_ = damage;
}

double Damage::swordDamage() {
    return swordDamage_;
}

void Damage::setSwordDamage(double damage) {
    swordDamage_ = damage;
}

