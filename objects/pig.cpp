
#include "pig.h"

Pig::Pig(QObject* parent) : Mob(parent)
{
    box() = QRectF(-100, -100, 200, 200);
    body() = {{-50, -25}, {50, -25}, {50, 25}, {-50, 25}};
    hitbox() = {{-50, -25}, {50, -25}, {50, 25}, {-50, 25}};
    useArea() = {{-60, -35}, {60, -35}, {60, 35}, {-60, 35}};
    setDamage(Damage(0, 0, 12));
    setDestination(pos());
    setMobSpeed(5);
}

void Pig::live() {
    std::mt19937 rnd(time(0));
    rotateToDestination();
    if (!isAgressive()) {
        if (dist(destination()) <= 30) {
            wait();
            QPointF dest = QPointF(cos(rnd() % 500 / 100), sin(rnd() % 500 / 100));
            setDestination(pos() + dest * (100 + rnd() % 200));
        }
    }

    move(speed());
    if (!await_) {
        move(direction() * mobSpeed());
    }

    if (isAgressive()) {
        setDestination(player()->pos());
    }

    if (dist(player()) >= 5000) {
        destroyObject();
    }

}

void Pig::interactWithObject(Object *obj) {
    if (isAgressive()) {
        if (scenePath(useArea()).intersects(obj->scenePath(obj->hitbox()))) {
            obj->getDamage(damage());
        }
    }
}

void Pig::interactWithPlayer(PlayerBase *obj) {
    if (isAgressive()) {
        if (scenePath(useArea()).intersects(obj->scenePath(obj->hitbox()))) {
            obj->getDamage(damage());
        }
    }
}

void Pig::getDamage(Damage damage) {
    health() -= damage.swordDamage();
    setAgressive(true);
    if (health() <= 0) {
        die();
    }
}

void Pig::wait(int ms) {
    await_ = true;
    QTimer::singleShot(ms, this, &Pig::start);

}
void Pig::start() {
    await_ = false;
}

