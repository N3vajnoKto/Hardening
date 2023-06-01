
#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <vector>
#include <QPixmap>


class AnimationManager
{
public:
    AnimationManager();
    std::vector<QPixmap>& frames();
private:
    std::vector<QPixmap> frames_;
};

#endif // ANIMATIONMANAGER_H
