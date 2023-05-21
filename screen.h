
#ifndef SCREEN_H
#define SCREEN_H


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QResizeEvent>
#include "object.h"
#include <QList>

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = nullptr);
    void setFocus(Object* obj);
    void mouseMoveEvent(QMouseEvent *event) override;
    QList<QGraphicsItem*> objectsNear(QGraphicsItem* it, QRectF rect);
    QGraphicsScene* hud();
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void addObject(Object* obj);
    void updateScreen();
signals:
    void mouseMoved(QPointF);

private:
    QGraphicsScene* scene_;
    QGraphicsScene* hud_;
    QGraphicsView* sceneView_;
    QGraphicsView* hudView_;
    const int sceneWidth = 1000000;
    const int sceneHeight = 1000000;

};

#endif // SCREEN_H
