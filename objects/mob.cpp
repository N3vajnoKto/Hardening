
#include "mob.h"

Mob::Mob(QObject* parent) : LootableObject(parent)
{
    box() = QRectF(-100, -100, 200, 200);
    body() = {{-50, -25}, {50, -25}, {50, 25}, {-50, 25}};
    hitbox() = {{-50, -25}, {50, -25}, {50, 25}, {-50, 25}};
    useArea() = {{-60, -35}, {60, -35}, {60, 35}, {-60, 35}};
    setDamage(Damage(0, 0, 12));
}

void Mob::getDamage(Damage damage) {
    health() -= damage.swordDamage();

    if (health() <= 0) {
        die();
    }
}

double Mob::rotateSpeed() const {
    return rotateSpeed_;
}
void Mob::setRotateSpeed(double speed) {
    rotateSpeed_ = speed;
}

double Mob::length(QPointF pnt) const {
    return sqrt(pnt.x() * pnt.x() + pnt.y() * pnt.y());
}

void Mob::rotateToDestination() {
    QPointF newDir1 = {direction().x() * cos(rotateSpeed()) - direction().y() * sin(rotateSpeed()),
                       direction().x() * sin(rotateSpeed()) + direction().y() * cos(rotateSpeed())};
    QPointF newDir2 = {direction().x() * cos(-rotateSpeed()) - direction().y() * sin(-rotateSpeed()),
                       direction().x() * sin(-rotateSpeed()) + direction().y() * cos(-rotateSpeed())};

    if (length(newDir1 - destination_) < length(newDir2 - destination_)) {
        setDirecton(newDir1);
    } else {
        setDirecton(newDir2);
    }
}

double Mob::mobSpeed() const {
    return mobSpeed_;
}
void Mob::setMobSpeed(double speed) {
    mobSpeed_ = speed;
}

QPointF Mob::destination() const {
    return destination_;
}
void Mob::setDestination(QPointF dest) {
    destination_ = dest;
}

QPointF Mob::direction() const {
    return direction_;
}

void Mob::setDirecton(QPointF pnt) {
    direction_ = normalize(pnt);
}
QPointF Mob::normalize(QPointF pnt) const {
    int len = length(pnt);
    if (pnt == QPointF(0, 0)) return pnt;
    pnt.rx() /= len;
    pnt.ry() /= len;

    return pnt;
}

bool Mob::isAgressive() const {
    return agressive_;
}

void Mob::setAgressive(bool bl) {
    agressive_ = bl;
}

Player* Mob::player() const {
    return player_;
}
void Mob::setPlayer(Player* player) {
    player_ = player;
}

