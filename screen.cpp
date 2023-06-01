
#include "screen.h"

#include <QGridLayout>

Screen::Screen(QWidget *parent)
    : QWidget{parent}, scene_(new QGraphicsScene(this)), sceneView_(new QGraphicsView(scene_, this)),
    hud_(new QGraphicsScene(this)), hudView_(new QGraphicsView(hud_, this))
{
    sceneView_->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    sceneView_->setSceneRect(-sceneWidth, -sceneHeight, 2 * sceneWidth, 2 * sceneHeight);
    sceneView_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sceneView_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sceneView_->setDragMode(QGraphicsView::NoDrag);
    sceneView_->setFocusPolicy(Qt::NoFocus);
    sceneView_->setCacheMode(QGraphicsView::CacheBackground);


    hudView_->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    hudView_->setSceneRect(QRect(0, 0, width(), height()));
    hudView_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    hudView_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    hudView_->setDragMode(QGraphicsView::NoDrag);
    hudView_->setFocusPolicy(Qt::NoFocus);

    QGridLayout* lay = new QGridLayout();

    lay->setContentsMargins(QMargins(0,0,0,0));
    lay->addWidget(sceneView_);
    setLayout(lay);
    sceneView_->setAttribute(Qt::WA_TransparentForMouseEvents);
    hudView_->setAttribute(Qt::WA_TransparentForMouseEvents);

    QPalette pal = hudView_->palette();
    pal.setColor(QPalette::Base, Qt::transparent);
    hudView_->setAutoFillBackground(true);
    hudView_->setPalette(pal);

    QPixmap bg;
    bg.load(":/icons/grass.png");
    bg = bg.scaled(128, 128);
    scene_->setBackgroundBrush(bg);

    setMouseTracking(true);

}

QPoint Screen::mouseCoord() const {
    return mouseCoord_;
}

void Screen::resizeEvent(QResizeEvent *event) {
    hudView_->resize(event->size().width(), event->size().height());
    hudView_->setSceneRect(QRect(0, 0, event->size().width() - 2, event->size().height() - 2));
}

void Screen::mouseMoveEvent(QMouseEvent *event) {
    mouseCoord_ = event->pos();
    emit mouseMoved(event->pos());
}

void Screen::mousePressEvent(QMouseEvent* event) {
    mouseCoord_ = event->pos();
    QGraphicsItem* item = hudView_->itemAt(event->pos());
    if (item != nullptr) {
        if (event->button() == Qt::LeftButton) {
            emit hudClicked(item, Keys::leftMouseButton);
        }
        if (event->button() == Qt::RightButton) {
            emit hudClicked(item, Keys::rightMouseButton);
        }

        return;
    } else {
        if (event->button() == Qt::LeftButton) {
            emit sceneClicked(sceneView()->mapToScene(event->pos()), Keys::leftMouseButton);
        }
        if (event->button() == Qt::RightButton) {
            emit sceneClicked(sceneView()->mapToScene(event->pos()), Keys::rightMouseButton);
        }

        return;
    }
}

void Screen::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        emit released(Keys::leftMouseButton);
    }
    if (event->button() == Qt::RightButton) {
        emit released(Keys::rightMouseButton);
    }
}

QGraphicsScene* Screen::hud() {
    return hud_;
}

QGraphicsScene* Screen::scene() {
    return scene_;
}

QGraphicsView* Screen::hudView() {
    return hudView_;
}
QGraphicsView* Screen::sceneView() {
    return sceneView_;
}

void Screen::addObject(ObjectBase* obj) {
    scene_->addItem(obj);
}

void Screen::updateScreen() {
    sceneView_->update();
    hudView_->update();
}

void Screen::setFocus(ObjectBase* obj) {
    sceneView_->centerOn(obj);
}


QList<QGraphicsItem*> Screen::objectsNear(QGraphicsItem* it, QRectF rect) {
    QRectF search = QRectF(it->pos() - QPointF(rect.width(), rect.height()) * 0.5, rect.size());
    return scene_->items(search);
}
