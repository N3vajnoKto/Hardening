
#include "toolaxe.h"
#include "objectaxe.h"

ToolAxe::ToolAxe(QObject *parent)
    : Tool{parent}
{
    setId("simpleAxe");
    setMaxNumber(1);
    setAxeDamage(10);
    setSwordDamage(3);
    setIcon(QIcon(":/icons/axe.png"));
    setUseRadius(200);
}

bool ToolAxe::useItem(QPointF pos) {
    if (usable()) {
        ObjectAxe* axe = new ObjectAxe(this);
        axe->setPlayer(player());
        double ang = (turn ? 1 : -1);
        axe->setAngle(turn ? 0.1 : -0.1);

        QPointF dir = player()->playerDirection();
        double nd = acos(dir.y());
        if (dir.x() < 0) nd = 2*M_PI - nd;
        axe->rotate(nd);
        axe->dir_ = QPointF(dir.x() * cos(ang) + dir.y() * sin(ang), -dir.x() * sin(ang) + dir.y() * cos(ang));
        axe->rotate(ang);

        axe->setPos(player()->pos() + axe->dir_ * 100);
        emit addObject(axe);
        startReload(reload());

        turn ^= true;
        return true;
    }

    return false;
}
