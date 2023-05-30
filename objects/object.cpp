
#include "object.h"

Object::Object(QObject* parent) : ObjectBase(parent)
{

}

void Object::setDamage(Damage damage) {
    damage_ = damage;
}

Damage Object::damage() const {
    return damage_;
}

bool Object::isSolidWithPlayer() const {
    return solidWithPlayer_;
}

void Object::setSolidWithPlayer(bool bl) {
    solidWithPlayer_ = bl;
}

void Object::die() {

}

void Object::interactWithPlayer(PlayerBase* player) {

}

void Object::interactWithPlayerBody(PlayerBase* player) {
    if (collidesWithItem(player)) {
        if (isSolidWithPlayer() && movePrior() <= player->movePrior()) {
            double l = 0;
            double r = std::max(box().width(), box().height());
            QPointF dir = normalize(pos() - player->pos());
            for (int i = 0; i < 5; ++i) {
                double sr = (l + r) / 2;
                move(sr * dir);
                if (collidesWithItem(player)) {
                    l = sr;
                } else {
                    r = sr;
                }
                move(-sr * dir);
            }

            move(r * dir);
        }
    }
}

void Object::interactWithObjectBody(Object* obj) {
    if (scenePath(body()).intersects(obj->scenePath(obj->body()))) {
        if (isSolid() && obj->isSolid() && movePrior() <= obj->movePrior()) {
            double l = 0;
            double r = std::max(box().width(), box().height());
            QPointF dir = normalize(pos() - obj->pos());
            for (int i = 0; i < 5; ++i) {
                double sr = (l + r) / 2;
                move(sr * dir);
                if (scenePath(body()).intersects(obj->scenePath(obj->body()))) {
                    l = sr;
                } else {
                    r = sr;
                }
                move(-sr * dir);
            }

            move(r * dir);
        }
    }
}

void Object::interactWithObject(Object* obj) {

}

