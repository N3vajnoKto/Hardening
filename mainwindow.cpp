
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), screen_(new Screen()), controller(new Controller(this)), timer(new QTimer(this))
{
    setCentralWidget(screen_);

    resize(700, 600);

    connect(controller, &Controller::objectAdded, screen_, &Screen::addObject);
    connect(controller, &Controller::updated, screen_, &Screen::updateScreen);

    connect(timer, &QTimer::timeout, controller, &Controller::update);
    connect(timer, &QTimer::timeout, this, &MainWindow::focusScreen);
    connect(screen_, &Screen::mouseMoved, controller, &Controller::updatePlayerDiraction);
    timer->start(16);

    screen_->addObject(controller->player());
    screen_->setFocus(controller->player());

    controller->setScreen(screen_);

    Object* test = new Object();

    test->setPos(QPointF(250, 250) );
    controller->addObject(test);

    Object* test1 = new Object();
    test1->rotate(0.5);

    test1->setPos(QPointF(180, 180) );
    controller->addObject(test1);
    setMouseTracking(true);

}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_W) {
        controller->movePlayer(Keys::KeyW);
    }

    if (event->key() == Qt::Key_S) {
        controller->movePlayer(Keys::KeyS);
    }

    if (event->key() == Qt::Key_A) {
        controller->movePlayer(Keys::KeyA);
    }

    if (event->key() == Qt::Key_D) {
        controller->movePlayer(Keys::KeyD);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_W) {
        controller->stopPlayer(Keys::KeyW);
    }

    if (event->key() == Qt::Key_S) {
        controller->stopPlayer(Keys::KeyS);
    }

    if (event->key() == Qt::Key_A) {
        controller->stopPlayer(Keys::KeyA);
    }

    if (event->key() == Qt::Key_D) {
        controller->stopPlayer(Keys::KeyD);
    }
}

void MainWindow::focusScreen() {
    screen_->setFocus(controller->focusOn());
}


