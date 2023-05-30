
#include "toolpickaxe.h"
#include "../objects/objectpickaxe.h"

ToolPickaxe::ToolPickaxe(QObject *parent)
    : Tool{parent}
{
    setId("simplePickaxe");
    setDamage(Damage(0, 10, 3));
    setIcon(QIcon(":/icons/pickaxe.png"));
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
        ObjectPickaxe* axe = new ObjectPickaxe(this);
        axe->setPlayer(player());
        double ang = (turn ? 1 : -1);
        axe->setAngle(turn ? 0.1 : -0.1);

        QPointF dir = player()->playerDirection();
        double nd = acos(dir.y());
        if (dir.x() < 0) nd = 2 * M_PI - nd;
        axe->rotate(nd);
        axe->dir_ = QPointF(dir.x() * cos(ang) + dir.y() * sin(ang), -dir.x() * sin(ang) + dir.y() * cos(ang));
        axe->rotate(ang);

        axe->setPos(player()->pos() + axe->dir_ * 100);
        axe->setDamage(damage());
        emit addObject(axe);
        startReload(reload());

        turn ^= true;
        return true;
    }

    return false;
}
