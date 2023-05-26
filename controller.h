
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <set>
#include <QKeyEvent>
#include <QTimer>
#include "object.h"
#include "player.h"
#include "screen.h"
#include "items.h"
#include "keys.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QObject* parent  = nullptr);
    void addObject(Object* obj);
    void deleteObject(Object* obj);
    Player* player();
    void movePlayer(Keys key);
    void stopPlayer(Keys key);
    Object* focusOn();
    void setFocus(Object* obj);
    Screen* screen();
    void setScreen(Screen* scr);
    void clearTrash();
    bool inventoryOpened() const;
    void buildHUD();
    void makeCurrentCell(int ind);
    void makeCurrentCell(Cell* ind);
    void updatePlayerDiraction(QPoint dir);
    void updatePicked(QPointF pos);
    void connectUsingItem(Item* item);
    void updateReleaseButton(Keys key);
private:
    std::set<Object*> objects_;
    std::set<Object*> objectTrash_;
    Player* player_;
    QTimer* timer;
    Object* focusOn_;
    Screen* screen_ = nullptr;
    bool inventoryOpened_ = false;
    Keys lastKey;
    QPointF lastPress;

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
