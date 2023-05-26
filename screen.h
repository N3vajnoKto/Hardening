
#ifndef SCREEN_H
#define SCREEN_H


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QResizeEvent>
#include "object.h"
#include "keys.h"
#include <QList>

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = nullptr);
    void setFocus(Object* obj);
    QList<QGraphicsItem*> objectsNear(QGraphicsItem* it, QRectF rect);
    QGraphicsScene* hud();
    QGraphicsScene* scene();
    QGraphicsView* hudView();
    QGraphicsView* sceneView();
    QPoint mouseCoord() const;

    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QGraphicsScene* scene_;
    QGraphicsScene* hud_;
    QGraphicsView* sceneView_;
    QGraphicsView* hudView_;
    const int sceneWidth = 1000000;
    const int sceneHeight = 1000000;
    QPoint mouseCoord_;

public slots:
    void addObject(Object* obj);
    void updateScreen();

signals:
    void mouseMoved(QPoint);
    void hudClicked(QGraphicsItem* item, Keys key);
    void sceneClicked(QPointF, Keys key);
    void released(Keys key);


};

#endif // SCREEN_H
