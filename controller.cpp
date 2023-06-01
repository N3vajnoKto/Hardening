
#include "controller.h"
#include <QPixmapCache>

Controller::Controller(QObject* parent) : QObject(parent), player_(new Player(this))
{
    loadIcons();
    focusOn_ = player_;
    connect(player_->inventory(), &Inventory::itemAdded, this, &Controller::connectUsingItem);
    ToolAxe* axe = new ToolAxe(this);
    ToolPickaxe* pickaxe = new ToolPickaxe(this);

    Item* item1 = new Item();
    ItemGroup* it1 = new ItemGroup(item1);
    it1->setCount(10);

    Item* item2 = new Item();
    ItemGroup* it2 = new ItemGroup(item2);
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

void Controller::loadIcons() {
    QPixmap pm;
    pm.load(":/icons/notImpl.png");
    QPixmapCache::insert("notImpl", pm);
    pm.load(":/icons/wood.png");
    QPixmapCache::insert("wood", pm);
    pm.load(":/icons/stone.png");
    QPixmapCache::insert("stone", pm);
    pm.load(":/icons/axe.png");
    QPixmapCache::insert("axe", pm);
    pm.load(":/icons/pickaxe.png");
    QPixmapCache::insert("pickaxe", pm);
    pm.load(":/icons/pickaxe.png");
    QPixmapCache::insert("pickaxe", pm);
    pm.load(":/icons/tree.png");
    QPixmapCache::insert("tree", pm.scaled(200, 200));
    pm.load(":/icons/cobblestone.png");
    QPixmapCache::insert("cobblestone", pm.scaled(200, 200));
    pm.load(":/icons/objectAxe.png");
    QPixmapCache::insert("objectAxe", pm);
    pm.load(":/icons/objectPickaxe.png");
    QPixmapCache::insert("objectPickaxe", pm);
}

void Controller::generateWorld() {

    for (int i = -2; i < 2; ++i) {
        for (int j = -2; j < 2; ++j) {
            generateChank(i, j);
        }
    }
    spawn();
}

void Controller::deleteObject(ObjectBase* object) {
    if (object != nullptr) {
        objectTrash_.insert(object);
    }
}

void Controller::addObject(ObjectBase* obj) {
    auto object = dynamic_cast<Object*>(obj);
    object->setZValue(int(object->y()));
    connect(object, &Object::objectDestroyed, this, &Controller::deleteObject);
    connect(object, &Object::objectAdded, this, &Controller::addObject);
    objects_.insert(object);
    screen_->addObject(object);
}

void Controller::addMob(Mob* mob) {
    mob->setPlayer(player());
    mob->setZValue(int(mob->y()));
    mobs_.insert(mob);
    connect(mob, &Mob::objectDestroyed, this, &Controller::deleteObject);
    connect(mob, &Mob::objectAdded, this, &Controller::addObject);
    screen_->addObject(mob);
}

Player* Controller::player() {
    return player_;
}

void Controller::removeItem(ItemBase* item) {
    if (items_.count(item)) {
        items_.erase(item);
    }
}

void Controller::connectUsingItem(ItemBase* item) {
    if (items_.count(item)) return;
    connect(item, &ItemBase::addObject, this, &Controller::addObject);
    connect(item, &ItemBase::itemDestroyed, this, &Controller::removeItem);
    items_.insert(item);
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
    for (Mob* mob : mobs_) {
        mob->live();
    }

    int xc = int(player()->pos().x()) / block_;
    int yc = int(player()->pos().y()) / block_;

    if (currentChank_ != std::make_pair(xc, yc)) {
        currentChank_ = {xc, yc};
        generateChank(xc, yc);
        generateChank(xc - 1, yc - 1);
        generateChank(xc + 1, yc + 1);
        generateChank(xc + 1, yc - 1);
        generateChank(xc - 1, yc + 1);
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
        auto mob = dynamic_cast<Mob*>(obj);
        if (object != nullptr) {
            player()->interactWithObjectBody(object);
            object->interactWithPlayerBody(player());
            if (object->isInteractive()) {
                object->interactWithPlayer(player());
            }
        }

        if (mob != nullptr) {
            mob->interactWithPlayerBody(player());
            if (mob->isInteractive()) {
                mob->interactWithPlayer(player());
            }
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

    for (Mob* obj : mobs_) {
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

void Controller::spawn() {
    QTimer::singleShot(2000, this, &Controller::spawn);
    if (mobs_.size() > 10) return;
    std::mt19937 rnd(time(0));
    if (rnd() % 1000 > 300) return;
    QPointF dir(cos((rnd() % 1000)/ 1000.0), sin((rnd() % 1000)/ 1000.0));
    QPointF ps = player()->pos() + dir * 1400;
    Pig* pig = new Pig();
    pig->setPos(ps);
    addMob(pig);

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
    if (chank_.count({x, y}) > 0) return;
    int seed = ((seed_ * x) % (abs(y) + 1)) * y - seed_ / (abs(x) + 1);
    std::mt19937 rnd(seed);

    int cnt = 5;

    cnt += rnd() % 10;

    int xc = (x > 0 ? x : x - 1) * block_;
    int yc = (y > 0 ? y : y - 1) * block_;
    int w = block_;
    int h = block_;

    if (x == 0) {
        w += block_;
        cnt += 10;
    }
    if (y == 0) {
        h += block_;
        cnt += 10;
    }


    for (int i = 0; i < cnt; ++i) {
        if ((rnd() % 1000) / 1000.0 < 0.7) {
            Tree* tree = new Tree();
            tree->setPos(xc + int(rnd() % w), yc + int(rnd() % h));

            while (intersects(tree)) {
                tree->setPos(xc + int(rnd() % w), yc + int(rnd() % h));
            }

            addLazyObject(tree);

        } else {
            Stone* stone = new Stone(this);
            stone->setPos(xc + int(rnd() % w), yc + int(rnd() % h));

            while (intersects(stone)) {
                stone->setPos(xc + int(rnd() % w), yc + int(rnd() % h));
            }

            addLazyObject(stone);
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
    object->setZValue(int(object->y()));
    connect(object, &Object::objectDestroyed, this, &Controller::deleteObject);
    connect(object, &Object::objectAdded, this, &Controller::addObject);
    lazyObjects_.insert(object);
    screen_->addObject(object);
}

void Controller::clearTrash() {
    for (auto* to : objectTrash_) {
        Object* obj = dynamic_cast<Object*> (to);
        if (objects_.count(obj)) {
            objects_.erase(obj);
        }
        if (lazyObjects_.count(obj)) {
            lazyObjects_.erase(obj);
        }
        Mob* mob = dynamic_cast<Mob*> (to);
        if (mobs_.count(mob)) {
            mobs_.erase(mob);
        }

        delete to;
    }

    objectTrash_.clear();
}
