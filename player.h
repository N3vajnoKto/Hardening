
#ifndef PLAYER_H
#define PLAYER_H

#include "playerbase.h"
#include "objects/object.h"
#include "animationmanager.h"
#include <QTimer>


class Player : public PlayerBase
{
public:
    Player(QObject* parent = nullptr);
    void interactWithObjectBody(Object* obj);
    AnimationManager animation;
    void nextAnimation();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // PLAYER_H
