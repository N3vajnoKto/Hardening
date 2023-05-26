
#include "player.h"

Player::Player(QObject* parent) : Object(parent), playerMovement_{0, 0}, inventory_(new Inventory(30, 10, this))
{
    setMovePrior(-1);
}

Inventory* Player::inventory() {
    return inventory_;
}

QPointF& Player::playerMovement() {
    return playerMovement_;
}

void Player::addPlayerMovement(QPointF move) {
    playerMovement_ += move;
}

QPointF Player::normalize(QPointF dir) {
    double len = sqrtl(dir.x() * dir.x() + dir.y() * dir.y());
    if (len == 0) return dir;
    dir.rx() /= len;
    dir.ry() /= len;

    return dir;
}

void Player::live() {
    move(speed());
    if (ableToMove) {
        move(playerSpeed_ * normalize(playerMovement_));
    }
}

QPointF& Player::playerDirection() {
    return playerDirection_;
}

void Player::setPlayerDirection(QPointF dir) {
    playerDirection_ = normalize(dir);
}

void Player::interactWithObject(Object* obj) {
    if (scenePath(hitbox()).intersects(obj->scenePath(obj->hitbox()))) {
//        qDebug() << "intersected";
//        obj->destroyObject();
    }
}
