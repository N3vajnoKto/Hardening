
#ifndef MOB_H
#define MOB_H


#include "lootableobject.h"

class Mob : public LootableObject
{
public:
    Mob(QObject* parent);
    Player* player() const;
    void setPlayer(Player* player);
    QPointF direction() const;
    void setDirecton(QPointF);
    QPointF normalize(QPointF) const;
    QPointF destination() const;
    void setDestination(QPointF dest);
    double mobSpeed() const;
    void setMobSpeed(double speed);
    double length(QPointF pnt) const;
    void rotateToDestination();
    double rotateSpeed() const;
    void setRotateSpeed(double speed);
    bool isAgressive() const;
    void setAgressive(bool bl);
    virtual void getDamage(Damage damage) override;
private:
    Player* player_ = nullptr;
    bool agressive_ = false;
    QPointF direction_ = {0, 1};
    QPointF destination_;
    double mobSpeed_ = 0;
    double rotateSpeed_ = 0.1;
};

#endif // MOB_H
