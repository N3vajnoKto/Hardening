
#include "controller.h"

Controller::Controller(QObject* parent) : QObject(parent), player_(new Player(this))
{
    focusOn_ = player_;
    ToolAxe* axe = new ToolAxe(this);
    connectUsingItem(axe);
    axe->setPlayer(player_);
    player()->inventory()->addItem(axe);
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

void Controller::connectUsingItem(Item* item) {
    connect(item, &Item::addObject, this, &Controller::addObject);
}

void Controller::updatePicked(QPointF pos) {
}

void Controller::updateMouse(QPoint pos) {
    updatePlayerDiraction(pos);
    lastPress = screen()->sceneView()->mapToScene(pos);
}

void Controller::updateSceneClicked(QPointF pos, Keys key) {
    lastKey = key;
    lastPress = pos;
}

void Controller::updateReleaseButton(Keys key) {
    if (key == lastKey) {
        lastKey = Keys::NONE;
    }
}

void Controller::updateClickHUD(QGraphicsItem* item, Keys key) {
    if (item == nullptr) return;

    Cell* cell = dynamic_cast<Cell*> (item);

    if (!inventoryOpened() && cell != nullptr) {
        makeCurrentCell(cell);
    }
    if (inventoryOpened() && cell != nullptr) {

        if (key == Keys::leftMouseButton) {
            if (player()->inventory()->picked() != nullptr && cell->item() != nullptr &&
                player()->inventory()->picked()->id() == cell->item()->id() && !cell->item()->full()) {
                cell->item()->addItem(player()->inventory()->picked());
                if (player()->inventory()->picked()->count() == 0) {
                    delete player()->inventory()->picked();
                    screen_->setCursor(Qt::ArrowCursor);
                    player()->inventory()->setPicked(nullptr);
                }
            } else {
                Item* tmp = cell->item();
                cell->setItem(player()->inventory()->picked());
                player()->inventory()->setPicked(tmp);

                if (tmp == nullptr) {
                    screen_->setCursor(Qt::ArrowCursor);
                } else {
                    screen_->setCursor(QCursor(tmp->pixmap(32, 32)));
                    player()->inventory()->setPicked(tmp);
                }
            }
        }

        if (key == Keys::rightMouseButton) {
            if (player()->inventory()->picked() != nullptr && cell->item() != nullptr &&
                player()->inventory()->picked()->id() == cell->item()->id() && !cell->item()->full()) {

                cell->item()->addCount(-1);
                player()->inventory()->picked()->addCount(1);

                if (player()->inventory()->picked()->count() == 0) {
                    delete player()->inventory()->picked();
                    screen_->setCursor(Qt::ArrowCursor);
                    player()->inventory()->setPicked(nullptr);
                }

                if (cell->item()->count() == 0) {
                    delete cell->item();
                    cell->setItem(nullptr);
                }

                screen_->setCursor(QCursor(player()->inventory()->picked()->pixmap(32, 32)));

            }
            if (player()->inventory()->picked() == nullptr) {
                cell->item()->addCount(-1);
                player()->inventory()->setPicked(new Item(cell->item()));
                player()->inventory()->picked()->setCount(1);

                if (cell->item()->count() == 0) {
                    delete cell->item();
                    cell->setItem(nullptr);
                }

                screen_->setCursor(QCursor(player()->inventory()->picked()->pixmap(32, 32)));
            }
        }
    }
}

void Controller::update() {

//    qDebug() << player()->direct() ;

    if (lastKey == Keys::leftMouseButton) {
        if (player()->inventory()->picked() != nullptr) {
            player()->inventory()->picked()->useItem(lastPress);
            if (!player()->inventory()->picked()->autouse()) {
                lastKey = Keys::NONE;
            }
            screen()->setCursor(QCursor(player()->inventory()->picked()->pixmap()));
            if (player()->inventory()->picked() ->count() <= 0) {
                delete player()->inventory()->picked();
                player()->inventory()->setPicked(nullptr);
            }
        } else if (player()->inventory()->current() != nullptr && player()->inventory()->current()->item() != nullptr){
            player()->inventory()->current()->item()->useItem(lastPress);
            if (!player()->inventory()->current()->item()->autouse()) {
                lastKey = Keys::NONE;
            }
            if (player()->inventory()->current()->item() -> count() <= 0) {
                delete player()->inventory()->current()->item();
                player()->inventory()->current()->setItem(nullptr);
            }
        }
    }

    player()->live();
    for (Object* obj : objects_) {
        obj->live();
    }

    QList<QGraphicsItem*> list = screen()->objectsNear(player(), player()->boundingRect());


    for (auto to : list) {
        Object* obj = dynamic_cast<Object*>(to);
        auto self = dynamic_cast<Player*>(to);
        if (self == player()) continue;
        if (obj->isInteractive()) {
            player()->interactWithObjectBody(obj);
        }
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

void Controller::updatePlayerDiraction(QPoint dir) {
    QPointF pnt = screen()->sceneView()->mapToScene(dir);
    pnt -= player()->pos();
    player_->setPlayerDirection(pnt);
}

Screen* Controller::screen() {
    return screen_;
}

void Controller::setScreen(Screen* scr) {
    screen_ = scr;
    connect(screen_, &Screen::hudClicked, this, &Controller::updateClickHUD);
    connect(screen_, &Screen::sceneClicked, this, &Controller::updateSceneClicked);
    connect(screen_, &Screen::released, this, &Controller::updateReleaseButton);
}

bool Controller::inventoryOpened() const {
    return inventoryOpened_;

}

void Controller::openInventory() {
    inventoryOpened_ ^= true;
    for (int i = player()->inventory()->row(); i < player()->inventory()->cells().size(); ++i) {
        if (!inventoryOpened()) {
            screen()->hud()->removeItem(player()->inventory()->at(i));
        } else {
            screen()->hud()->addItem(player()->inventory()->at(i));
        }
    }

    if (!inventoryOpened()) {
        if (player()->inventory()->picked() != nullptr) {
            player()->inventory()->addItem(player()->inventory()->picked());
            player()->inventory()->setPicked(nullptr);
            screen_->setCursor(Qt::ArrowCursor);
        }
    }

}

void Controller::makeCurrentCell(int ind) {
    if (ind < 0 || ind >= player()->inventory()->row()) return;
    player()->inventory()->makeCurrent(player()->inventory()->at(ind));
}

void Controller::makeCurrentCell(Cell* cell) {
    player()->inventory()->makeCurrent(cell);
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
