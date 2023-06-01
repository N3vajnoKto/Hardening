
#include "pig.h"
#include "../items/meat.h"

Pig::Pig(QObject* parent) : Mob(parent)
{
    box() = QRectF(-100, -100, 200, 200);
    body() = {{-50, -25}, {50, -25}, {50, 25}, {-50, 25}};
    hitbox() = {{-50, -25}, {50, -25}, {50, 25}, {-50, 25}};
    useArea() = {{-60, -35}, {60, -35}, {60, 35}, {-60, 35}};
    setDamage(Damage(0, 0, 12));
    setDestination(pos());
    setMobSpeed(2);
    loot() = {SpawnOption(new Meat(), 1, 2, 0.9), SpawnOption(new Meat(), 1, 2, 0.5)};
}

void Pig::stopChilling() {
    chill_ = false;
}

void Pig::calm() {
    setAgressive(false);
    setMobSpeed(2);
}

void Pig::changeDestination() {
    if (isAgressive()) return;
    std::mt19937 rnd(time(0));
    wait(rnd() % 3000);
    if (chill_) {
        QPointF dest = QPointF(cos(rnd() % 300 / 100), sin(rnd() % 300 / 100));
        setDestination(pos() + dest * (100 + rnd() % 100));
    } else {
        chill_ = true;
        QPointF dest = QPointF(cos(rnd() % 300 / 100), sin(rnd() % 300 / 100));
        setDestination(pos() + dest * (300 + rnd() % 300));
    }

    QTimer::singleShot(5000, this, &Pig::stopChilling);
    QTimer::singleShot(10000, this, &Pig::changeDestination);
}

void Pig::live() {
    rotateToDestination();

    if (!isAgressive() && (dist(destination() - pos()) <= 100 || dist(destination() - pos()) >= 2000) ) {
        changeDestination();
    }

    move(speed());
    speed() *= 0.7;
    if (!await_) {
        move(direction() * mobSpeed());
    }

    if (isAgressive()) {
        setDestination(player()->pos());
    }

    if (dist(player()) >= 5000) {
        destroyObject();
    }

    if (dist(player()) >= 1500) {
        calm();
    }

}

void Pig::interactWithObject(Object *obj) {
//    if (isAgressive()) {
//        if (scenePath(useArea()).intersects(obj->scenePath(obj->hitbox()))) {
//            obj->getDamage(damage());
//        }
//    }
}

void Pig::interactWithPlayer(PlayerBase *obj) {
    if (isAgressive()) {
        if (scenePath(useArea()).intersects(obj->scenePath(obj->hitbox()))) {
            obj->getDamage(damage());
            QPointF dir = normalize(obj->pos() - pos());

            obj->speed() += dir * 30;
        }
    }
}

void Pig::getDamage(Damage damage) {
    health() -= damage.swordDamage();
    setAgressive(true);
    setMobSpeed(5);
    start();
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

