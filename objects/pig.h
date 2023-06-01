
#ifndef PIG_H
#define PIG_H

#include "mob.h"
#include "../animationmanager.h"
#include <QTimer>

class Pig : public Mob
{
public:
    Pig(QObject* parent = nullptr);
    void live();
    void wait(int ms = 4000);
    void start();
    void getDamage(Damage damage) override;
    void interactWithObject(Object *obj) override;
    void interactWithPlayer(PlayerBase *obj) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void calm();
    void changeDestination();
    void stopChilling();
    void nextAnimation();
    AnimationManager animation;
private:
    bool await_ = false;
    bool chill_ = false;

};

#endif // PIG_H
