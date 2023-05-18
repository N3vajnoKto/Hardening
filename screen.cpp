
#include "screen.h"

#include <QGridLayout>
#include "object.h"

Screen::Screen(QGraphicsScene *parent)
    : QGraphicsView{parent}, scene(new QGraphicsScene(this))
{
    setScene(scene);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setSceneRect(-sceneWidth, -sceneHeight, 2 * sceneWidth, 2 * sceneHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragMode(QGraphicsView::NoDrag);
    setFocusPolicy(Qt::NoFocus);
    setMouseTracking(true);
}

void Screen::addObject(Object* obj) {
    scene->addItem(obj);
}

void Screen::updateScreen() {
    update();
}

void Screen::setFocus(Object* obj) {
    centerOn(obj);
}

void Screen::mouseMoveEvent(QMouseEvent *event) {
    QPointF dir = event->pos();
    dir.rx() -= width() / 2;
    dir.ry() -= height() / 2;
    emit mouseMoved(dir);
}

QList<QGraphicsItem*> Screen::objectsNear(QGraphicsItem* it, QRectF rect) {
    QRectF search = QRectF(it->pos() - QPointF(rect.width(), rect.height()) * 0.5, rect.size());
    auto lst = scene->items(search);
    return scene->items(search);
}

