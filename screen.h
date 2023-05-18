
#ifndef SCREEN_H
#define SCREEN_H


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "object.h"
#include <QList>

class Screen : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Screen(QGraphicsScene *parent = nullptr);
    QGraphicsScene* scene;
    void setFocus(Object* obj);
    void mouseMoveEvent(QMouseEvent *event) override;
    QList<QGraphicsItem*> objectsNear(QGraphicsItem* it, QRectF rect);

public slots:
    void addObject(Object* obj);
    void updateScreen();
signals:
    void mouseMoved(QPointF);

private:
    const int sceneWidth = 1000000;
    const int sceneHeight = 1000000;

};

#endif // SCREEN_H
