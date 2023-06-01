
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <set>
#include <QKeyEvent>
#include <QTimer>
#include "objects/objectbase.h"
#include "player.h"
#include "screen.h"
#include "items.h"
#include "keys.h"
#include "objects.h"
#include "objects/droppeditemobject.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QObject* parent  = nullptr);

    void addObject(ObjectBase* obj);
    void deleteObject(ObjectBase* obj);

    Player* player();
    void movePlayer(Keys key);
    void stopPlayer(Keys key);

    Screen* screen();
    void setScreen(Screen* scr);

    ObjectBase* focusOn();
    void setFocus(ObjectBase* obj);

    bool inventoryOpened() const;
    void buildHUD();

    void makeCurrentCell(int ind);
    void makeCurrentCell(Cell* ind);
    void connectUsingItem(ItemBase* item);
    void dropItem(ItemGroup* item, QPointF dir);

    void updatePlayerDiraction(QPoint dir);
    void updatePicked(QPointF pos);
    void updateReleaseButton(Keys key);
    void updatePlayerAction();
    void clearTrash();
    void generateChank(int x, int y);
    void addLazyObject(ObjectBase*);
    bool intersects(ObjectBase*);
    void addMob(Mob*);
    void generateWorld();
    void spawn();
    void removeItem(ItemBase* item);
    void loadIcons();
private:
    std::set<Object*> objects_;
    std::set<Mob*> mobs_;
    std::set<Object*> lazyObjects_;
    std::set<ObjectBase*> objectTrash_;
    std::set<ItemBase*> items_;
    Player* player_;
    QTimer* timer;
    ObjectBase* focusOn_;
    Screen* screen_ = nullptr;
    bool inventoryOpened_ = false;
    Keys lastKey;
    QPointF lastPress;
    std::set<std::pair<int, int> > chank_;
    int block_ = 1000;
    int seed_ = 14234;
    std::pair<int, int> currentChank_ = {-1, -1};

public slots:
    void updateClickHUD(QGraphicsItem* item, Keys key);
    void updateSceneClicked(QPointF pos, Keys key);
    void update();
    void updateMouse(QPoint pos);
    void openInventory();

signals:
    void objectAdded(Object* obj);
    void updated();
};

#endif // CONTROLLER_H
