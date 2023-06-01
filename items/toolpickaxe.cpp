
#include "toolpickaxe.h"
#include "../objects/objectpickaxe.h"

ToolPickaxe::ToolPickaxe(QObject *parent)
    : Tool{parent}
{
    setId("simplePickaxe");
    setDamage(Damage(0, 10, 17));
    QPixmap pm;
    QPixmapCache::find("pickaxe", &pm);
    setIcon(QIcon(pm));
    setUseRadius(200);
    setDisposable(false);
}

ToolPickaxe::ToolPickaxe(const ToolPickaxe *parent) : Tool{parent} {
    this->turn = parent->turn;
}

ItemBase* ToolPickaxe::copy() const {
    return new ToolPickaxe(this);
}

bool ToolPickaxe::useItem(QPointF pos) {
    if (usable()) {
        ObjectPickaxe* axe = new ObjectPickaxe();
        axe->setPlayer(player());
        double ang = (turn ? 1 : -1);
        axe->setAngle(turn ? 0.1 : -0.1);

        if (!turn) {
            axe->look_ = axe->look_.transformed(QTransform::fromScale(-1, 1));
        }

        QPointF dir = player()->playerDirection();
        double nd = acos(dir.y());
        if (dir.x() < 0) nd = 2*M_PI - nd;
        axe->rotate(nd);

        int pw = axe->look_.width();
        int ph = axe->look_.height();
        axe->look_ = axe->look_.transformed(QTransform().rotateRadians(-nd));
        axe->look_ = axe->look_.copy((axe->look_.width() - pw)/2, (axe->look_.height() - ph)/2, pw, ph);

        axe->dir_ = QPointF(dir.x() * cos(ang) + dir.y() * sin(ang), -dir.x() * sin(ang) + dir.y() * cos(ang));
        axe->rotate(ang);

        pw = axe->look_.width();
        ph = axe->look_.height();
        axe->look_ = axe->look_.transformed(QTransform().rotateRadians(-ang));
        axe->look_ = axe->look_.copy((axe->look_.width() - pw)/2, (axe->look_.height() - ph)/2, pw, ph);

        axe->setPos(player()->pos() + axe->dir_ * 100);
        axe->setDamage(damage());
        emit addObject(axe);
        startReload(reload());

        turn ^= true;
        return true;
    }

    return false;
}
