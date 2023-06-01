
#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <vector>
#include <QPixmap>


class AnimationManager
{
public:
    AnimationManager();
    std::vector<QPixmap>& framesLeft();
    std::vector<QPixmap>& framesRight();
    std::vector<QPixmap>& staying();
    QPixmap current;
    int ind = 0;
private:
    std::vector<QPixmap> framesLeft_;
    std::vector<QPixmap> framesRight_;
    std::vector<QPixmap> staying_;
};

#endif // ANIMATIONMANAGER_H
