
#include "droppeditemobject.h"
#include <QTimer>

DroppedItemObject::DroppedItemObject(ItemGroup* item, QObject* parent) : Object(parent)
{
    item_ = item;
    box() = QRectF(-15, -15, 30, 30);
    body() = {{-15, -15}, {15, -15}, {15, 15}, {-15, 15}};
    useArea() = body();
    hitbox() = body();
    setSolid(true);
    setInteractive(false);
    setMovePrior(-1000);
    QTimer::singleShot(1000, this, &DroppedItemObject::makeInteractive);
}

DroppedItemObject::~DroppedItemObject() {
    delete item_;
}

void DroppedItemObject::makeInteractive() {
    setInteractive(true);
}

ItemGroup* DroppedItemObject::item() {
    return item_;
}

void DroppedItemObject::setItem(ItemGroup* item) {
    item_ = item;
}

PlayerBase* DroppedItemObject::player() {
    return player_;
}

void DroppedItemObject::setPlayer(PlayerBase* player) {
    player_ = player;
}

void DroppedItemObject::live() {
    move(speed());
    speed() *= 0.7;
}

void DroppedItemObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->save();
    Q_UNUSED(option);
    Q_UNUSED(widget);

    int x = box().x();
    int y = box().y();

    if (item() != nullptr) {
        int width = box().width();
        int height = box().height();
        if (item()->count() > 1) {
            painter->drawPixmap(x + 4, y, item()->item()->icon().pixmap(width - 4, height - 4));
            QPixmap pix = item()->item()->icon().pixmap(width - 4, height - 4);
            QPainter pnt(&pix);
            pnt.setCompositionMode(QPainter::CompositionMode_SourceIn);
            pnt.fillRect(pix.rect(), QColor(0, 0, 0, 50));
            pnt.end();
            painter->drawPixmap(x + 4, y, pix);
            painter->drawPixmap(x, y + 4, item()->item()->icon().pixmap(width - 4, height - 4));
        } else {
            painter->drawPixmap(x, y, item()->item()->icon().pixmap(width, height));
        }

    }

    painter->restore();
}

void DroppedItemObject::interactWithPlayer(PlayerBase *player) {
    if (isInteractive()) {
        if (player->dist(this) < 10) {
            if (player->inventory()->addItem(item())) {
                item_ = nullptr;
                destroyObject();
            }
        }

        if (player->dist(this) < 100) {
            QPointF dir = player->pos() - pos();
            dir = player->normalize(dir);
            move(dir * 5);
        }
    }
}
