
#include "playerbase.h"
#include <QTimer>

PlayerBase::PlayerBase(QObject* parent) : ObjectBase(parent), playerMovement_{0, 0}, inventory_(new Inventory(30, 10, this))
{
    setMovePrior(-1);
}

Inventory* PlayerBase::inventory() {
    return inventory_;
}

QPointF& PlayerBase::playerMovement() {
    return playerMovement_;
}

void PlayerBase::addPlayerMovement(QPointF move) {
    playerMovement_ += move;
}

QPointF PlayerBase::normalize(QPointF dir) {
    double len = sqrtl(dir.x() * dir.x() + dir.y() * dir.y());
    if (len == 0) return dir;
    dir.rx() /= len;
    dir.ry() /= len;

    return dir;
}

void PlayerBase::makeMortal() {
    setImortal(false);
}

void PlayerBase::live() {
    speed() *= 0.7;
    move(speed());
    if (ableToMove) {
        move(playerSpeed_ * normalize(playerMovement_));
    }
}

QPointF& PlayerBase::playerDirection() {
    return playerDirection_;
}

void PlayerBase::setPlayerDirection(QPointF dir) {
    playerDirection_ = normalize(dir);
}

void PlayerBase::interactWithObject(ObjectBase* obj) {
}

void PlayerBase::getDamage(Damage damage) {
    if (isImortal()) return;
    health() -= damage.swordDamage();
    setImortal(true);

    if (health() <= 0) {
        setPos(0,0);
        health() = 100;
    }
    QTimer::singleShot(1000, this, &PlayerBase::makeMortal);
}
