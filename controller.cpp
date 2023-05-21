
#include "controller.h"

Controller::Controller(QObject* parent) : QObject(parent), player_(new Player(this))
{
    focusOn_ = player_;
}

void Controller::deleteObject(Object* obj) {
    objectTrash_.insert(obj);
}

void Controller::addObject(Object* obj) {
    connect(obj, &Object::objectDestroyed, this, &Controller::deleteObject);
    objects_.insert(obj);
    emit objectAdded(obj);
}

Player* Controller::player() {
    return player_;
}

void Controller::update() {
    for (Object* obj : objects_) {
        obj->live();
    }
    player()->live();

    QList<QGraphicsItem*> list = screen()->objectsNear(player(), player()->boundingRect());


    for (auto to : list) {
        Object* obj = dynamic_cast<Object*>(to);
        auto self = dynamic_cast<Player*>(to);
        if (self == player()) continue;
        player()->interactWithObjectBody(obj);
    }

    for (auto to : list) {
        Object* obj = dynamic_cast<Object*>(to);
        auto self = dynamic_cast<Player*>(to);
        if (self == player()) continue;
        player()->interactWithObject(obj);
    }


//    for (Object* obj : objects_) {
//        list = screen()->objectsNear(obj, obj->boundingRect());

//        for (auto to : list) {
//            Object* sobj = dynamic_cast<Object*>(to);
//            obj->interactWithObjectBody(sobj);
//        }
//    }



    clearTrash();
    emit updated();
}

void Controller::movePlayer(Keys key) {
    if (key == Keys::KeyW) {
        player_->addPlayerMovement(Move::forward);
    }

    if (key == Keys::KeyS) {
        player_->addPlayerMovement(Move::back);
    }

    if (key == Keys::KeyA) {
        player_->addPlayerMovement(Move::left);
    }

    if (key == Keys::KeyD) {
        player_->addPlayerMovement(Move::right);
    }
}

void Controller::stopPlayer(Keys key) {
    if (key == Keys::KeyW) {
        player_->addPlayerMovement(-Move::forward);
    }

    if (key == Keys::KeyS) {
        player_->addPlayerMovement(-Move::back);
    }

    if (key == Keys::KeyA) {
        player_->addPlayerMovement(-Move::left);
    }

    if (key == Keys::KeyD) {
        player_->addPlayerMovement(-Move::right);
    }
}

Object* Controller::focusOn() {
    return focusOn_;
}

void Controller::setFocus(Object* obj) {
    focusOn_ = obj;
}

void Controller::updatePlayerDiraction(QPointF dir) {
    player_->setPlayerDirection(dir);
}

Screen* Controller::screen() {
    return screen_;
}

void Controller::setScreen(Screen* scr) {
    screen_ = scr;
}

bool Controller::inventoryOpened() const {
    return inventoryOpened_;

}

void Controller::openInventory() {
    for (int i = player()->inventory()->row(); i < player()->inventory()->cells().size(); ++i) {
        if (inventoryOpened()) {
            screen()->hud()->removeItem(player()->inventory()->at(i));
        } else {
            screen()->hud()->addItem(player()->inventory()->at(i));
        }
    }

    inventoryOpened_ ^= true;

}

void Controller::makeCurrentCell(int ind) {
    if (ind < 0 || ind >= player()->inventory()->row()) return;
    player()->inventory()->makeCurrent(player()->inventory()->at(ind));
}

void Controller::buildHUD() {
    for (int i = 0; i < player()->inventory()->row(); ++i) {
        screen()->hud()->addItem(player()->inventory()->at(i));
    }
}

void Controller::clearTrash() {
    for (auto* to : objectTrash_) {
        if (objects_.count(to)) {
            objects_.erase(to);
        }
        delete to;
    }

    objectTrash_.clear();
}
