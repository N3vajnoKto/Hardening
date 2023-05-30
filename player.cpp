
#include "player.h"

Player::Player(QObject* parent) : PlayerBase(parent)
{

}

void Player::interactWithObjectBody(Object* obj) {
    if (scenePath(body()).intersects(obj->scenePath(obj->body()))) {
        if (obj->isSolidWithPlayer() && movePrior() <= obj->movePrior()) {
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
