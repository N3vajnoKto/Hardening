
#include "controller.h"

Controller::Controller(QObject* parent) : QObject(parent), player_(new Player(this))
{
    focusOn_ = player_;
    connect(player_->inventory(), &Inventory::itemAdded, this, &Controller::connectUsingItem);
    ToolAxe* axe = new ToolAxe(this);
    ToolPickaxe* pickaxe = new ToolPickaxe(this);
    connectUsingItem(axe);
    connectUsingItem(pickaxe);

    Item* item1 = new Item();
    ItemGroup* it1 = new ItemGroup(item1);
    it1->setCount(10);

    Item* item2 = new Item();
    ItemGroup* it2 = new ItemGroup(item1);
    it2->setCount(14);

    player()->inventory()->addItem(it1);
    player()->inventory()->addItem(it2);

    axe->setPlayer(player_);
    ItemGroup* axeGroup = new ItemGroup(axe);
    axeGroup->setCount(1);
    axe->setMaxNumber(1);
    player()->inventory()->addItem(axeGroup);

    pickaxe->setPlayer(player_);
    ItemGroup* pickaxeGroup = new ItemGroup(pickaxe);
    pickaxeGroup->setCount(1);
    pickaxe->setMaxNumber(1);
    player()->inventory()->addItem(pickaxeGroup);

}

void Controller::generateWorld() {
    objects_.clear();
    lazyObjects_.clear();

    for (int i = -10; i < 10; ++i) {
        for (int j = -10; j < 10; ++j) {
            generateChank(i, j);
        }
    }
}

void Controller::deleteObject(ObjectBase* obj) {
    Object* object = dynamic_cast<Object*>(obj);
    if (object != nullptr) {
        objectTrash_.insert(object);
    }
}

void Controller::addObject(ObjectBase* obj) {
    auto object = dynamic_cast<Object*>(obj);
    connect(object, &Object::objectDestroyed, this, &Controller::deleteObject);
    connect(object, &Object::objectAdded, this, &Controller::addObject);
    objects_.insert(object);
    screen_->addObject(object);
}

Player* Controller::player() {
    return player_;
}

void Controller::connectUsingItem(ItemBase* item) {
    connect(item, &ItemBase::addObject, this, &Controller::addObject);
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
                player()->inventory()->picked()->item()->id() == cell->item()->item()->id() && !cell->item()->full()) {
                cell->item()->addItemGroup(player()->inventory()->picked());
                if (player()->inventory()->picked()->count() == 0) {
                    delete player()->inventory()->picked();
                    screen_->setCursor(Qt::ArrowCursor);
                    player()->inventory()->setPicked(nullptr);
                } else {
                    screen_->setCursor(QCursor(player()->inventory()->picked()->pixmap(32, 32)));
                }
            } else {
                ItemGroup* tmp = cell->item();
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
                player()->inventory()->picked()->item()->id() == cell->item()->item()->id() && !cell->item()->full()) {

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
            if (player()->inventory()->picked() == nullptr && cell->item() != nullptr) {
                player()->inventory()->setPicked(new ItemGroup(cell->item()->item()->copy()));
                connectUsingItem(player()->inventory()->picked()->item());
                player()->inventory()->picked()->setCount(1);
                cell->item()->addCount(-1);

                if (cell->item()->count() == 0) {
                    delete cell->item();
                    cell->setItem(nullptr);
                }

                screen_->setCursor(QCursor(player()->inventory()->picked()->pixmap(32, 32)));
            }
        }
    }
}

void Controller::updatePlayerAction() {
    if (lastKey == Keys::leftMouseButton) {
        if (player()->inventory()->picked() != nullptr) {
            player()->inventory()->picked()->useItem(lastPress);
            if (!player()->inventory()->picked()->item()->autouse()) {
                lastKey = Keys::NONE;
            }
            screen()->setCursor(QCursor(player()->inventory()->picked()->pixmap(32, 32)));
            if (player()->inventory()->picked()->count() <= 0) {
                delete player()->inventory()->picked();
                player()->inventory()->setPicked(nullptr);
                screen()->setCursor(Qt::ArrowCursor);
            }
        } else if (player()->inventory()->current() != nullptr && player()->inventory()->current()->item() != nullptr){
            player()->inventory()->current()->item()->useItem(lastPress);
            if (!player()->inventory()->current()->item()->item()->autouse()) {
                lastKey = Keys::NONE;
            }
            if (player()->inventory()->current()->item()->count() <= 0) {
                delete player()->inventory()->current()->item();
                player()->inventory()->current()->setItem(nullptr);
            }
        }
    }

    if (lastKey == Keys::rightMouseButton) {
        lastKey = Keys::NONE;
        if (player()->inventory()->picked() != nullptr) {
            dropItem(player()->inventory()->picked(), player()->playerDirection() * 20);
            player()->inventory()->setPicked(nullptr);
            screen()->setCursor(Qt::ArrowCursor);
        }
    }
}

void Controller::update() {
    updatePlayerAction();
    player()->live();
    for (Object* obj : objects_) {
        obj->live();
    }

    int xc = int(player()->pos().x()) / block_;
    int yc = int(player()->pos().y()) / block_;

    if (currentChank_ != std::make_pair(xc, yc)) {
        currentChank_ = {xc, yc};
        generateChank(xc, yc);
        generateChank(xc - 1, yc - 1);
        generateChank(xc + 1, yc + 1);
        generateChank(xc + 1, yc - 1);
        generateChank(xc, yc + 1);
        generateChank(xc, yc - 1);
        generateChank(xc + 1, yc);
        generateChank(xc - 1, yc);
    }

    QList<QGraphicsItem*> list = screen()->objectsNear(player(), player()->boundingRect());


    for (auto to : list) {
        ObjectBase* obj = dynamic_cast<ObjectBase*>(to);

        auto self = dynamic_cast<Player*>(to);
        if (self == player()) continue;
        auto object = dynamic_cast<Object*>(obj);
        if (object == nullptr) continue;
        object->interactWithPlayer(player());
        if (object->isInteractive()) {
            player()->interactWithObjectBody(object);
        }
    }

    for (Object* obj : objects_) {
        list = screen()->objectsNear(obj, obj->boundingRect());
        for (auto to : list) {
            ObjectBase* sobj = dynamic_cast<ObjectBase*>(to);
            Object* object = dynamic_cast<Object*>(sobj);
            if (obj == object) continue;
            if (object == nullptr) continue;
            obj->interactWithObjectBody(object);
            obj->interactWithObject(object);
        }
    }

    clearTrash();
    emit updated();
}

bool Controller::intersects(ObjectBase* obj) {
//    auto lst = screen()->objectsNear(obj, obj->box());
//    for (auto* to : lst) {
//        ObjectBase* sobj = dynamic_cast<ObjectBase*> (to);
//        if (obj->scenePath(obj->body()).intersects(sobj->scenePath(sobj->body())) ) {
//            return true;
//        }
//    }

    return false;
}

void Controller::generateChank(int x, int y) {
    qDebug() << x << ' ' << y << ' ' << objects_.size();
    if (chank_.count({x, y})) return;
    int seed = ((seed_ * x) % (abs(y) + 1)) * y - seed_ / (abs(x) + 1);
    std::mt19937 rnd(seed);

    int cnt = 5;

    cnt += rnd() % 5;

    int xc = (x - 1) * block_;
    int yc = (y - 1) * block_;
    int w = block_;
    int h = block_;

    if (x == 0) {
        w += block_;
    }
    if (y == 0) {
        h += block_;
    }


    for (int i = 0; i < cnt; ++i) {
        if ((rnd() % 1000) / 1000.0 < 0.7) {
            Tree* tree = new Tree();
//            tree->setPos(xc + int(rnd() % w), yc + int(rnd() % h));

//            while (intersects(tree)) {
//                tree->setPos(xc + int(rnd() % w), yc + int(rnd() % h));
//            }

//            addLazyObject(tree);

//        } else {
//            Stone* stone = new Stone(this);
//            stone->setPos(xc + int(rnd() % w), yc + int(rnd() % h));

//            while (intersects(stone)) {
//                stone->setPos(xc + int(rnd() % w), yc + int(rnd() % h));
//            }

//            addLazyObject(stone);
        }
    }

    chank_.insert({x, y});

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

ObjectBase* Controller::focusOn() {
    return focusOn_;
}

void Controller::setFocus(ObjectBase* obj) {
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

void Controller::dropItem(ItemGroup* item, QPointF dir) {
    auto obj = new DroppedItemObject(item, this);
    obj->setPos(player()->pos());
    obj->speed() = dir;
    addObject(obj);

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

void Controller::addLazyObject(ObjectBase* obj) {
    auto object = dynamic_cast<Object*>(obj);
//    connect(object, &Object::objectDestroyed, this, &Controller::deleteObject);
//    connect(object, &Object::objectAdded, this, &Controller::addObject);
    lazyObjects_.insert(object);
    screen_->addObject(object);
}

void Controller::clearTrash() {
    for (auto* to : objectTrash_) {
        if (objects_.count(to)) {
            objects_.erase(to);
        }
        if (lazyObjects_.count(to)) {
            lazyObjects_.erase(to);
        }
        delete to;
    }

    objectTrash_.clear();
}
