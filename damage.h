
#ifndef DAMAGE_H
#define DAMAGE_H


class Damage
{
public:
    Damage(int axe = 0, int pickaxe = 0, int sword = 0);
    double axeDamage();
    void setAxeDamage(double damage);

    double pickaxeDamage();
    void setPickaxeDamage(double damage);

    double swordDamage();
    void setSwordDamage(double damage);

private:
    double axeDamage_ = 0;
    double pickaxeDamage_ = 0;
    double swordDamage_ = 0;
};

#endif // DAMAGE_H
