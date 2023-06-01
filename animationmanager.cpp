
#include "animationmanager.h"

AnimationManager::AnimationManager()
{

}

std::vector<QPixmap>& AnimationManager::framesLeft() {
    return framesLeft_;
}

std::vector<QPixmap>& AnimationManager::framesRight() {
    return framesRight_;
}

std::vector<QPixmap>& AnimationManager::staying() {
    return staying_;
}
