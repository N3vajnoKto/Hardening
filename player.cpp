
#include "player.h"
#include <QPixmapCache>

Player::Player(QObject* parent) : PlayerBase(parent)
{
    QPixmap pm;
    QPixmapCache::find("player", &pm);

    int w = pm.width() / 10;
    int h = pm.height() / 8;

    qDebug() << w << ' ' << h;

    animation.framesLeft().push_back(pm.copy(QRect(2 * w, 4 * h, w, h)));
    animation.framesLeft().push_back(pm.copy(QRect(6 * w, 4 * h, w, h)));
    animation.framesLeft().push_back(pm.copy(QRect(7 * w, 4 * h, w, h)));

    animation.framesRight().push_back(pm.copy(QRect(2 * w, 6 * h, w, h)));
    animation.framesRight().push_back(pm.copy(QRect(5 * w, 6 * h, w, h)));
    animation.framesRight().push_back(pm.copy(QRect(7 * w, 6 * h, w, h)));

    animation.staying().push_back(pm.copy(QRect(0, 0, w, h)));
    animation.staying().push_back(pm.copy(QRect(0, 2 * h, w, h)));

    nextAnimation();
}

void Player::nextAnimation() {
    if (playerMovement() == QPointF(0, 0)) {
        if (playerDirection().y() < 0) {
            animation.current = animation.staying()[1];
        } else {
            animation.current = animation.staying()[0];
        }
        animation.ind = 1;
    } else {
        animation.ind ++;
        animation.ind %= animation.framesLeft().size();
        if (playerMovement().y() > 0) {
            animation.current = animation.framesLeft()[animation.ind];
        } else {
            animation.current = animation.framesRight()[animation.ind];
        }
    }
    QTimer::singleShot(100, this, &Player::nextAnimation);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->save();


    painter->drawPixmap(box().x() + 10, box().y(), animation.current);
    painter->drawPath(path(hitbox()));

    painter->restore();
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
