
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <set>
#include <QKeyEvent>
#include <QTimer>
#include "object.h"
#include "player.h"
#include "screen.h"

enum class Keys{
    KeyW,
    KeyS,
    KeyA,
    KeyD,
    KeyEsc

};

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
private:
    std::set<Object*> objects_;
    std::set<Object*> objectTrash_;
    Player* player_;
    QTimer* timer;
    Object* focusOn_;
    Screen* screen_ = nullptr;
    bool inventoryOpened_ = false;

public slots:
    void update();
    void updatePlayerDiraction(QPointF dir);
    void openInventory();

signals:
    void objectAdded(Object* obj);
    void updated();
};

#endif // CONTROLLER_H
