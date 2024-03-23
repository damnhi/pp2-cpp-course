#include "enemy.h"
bool Enemy::isAlieve() const
{
    if (currentlifePoints_>0) return true;
    else return false;
}
int Enemy::lifePercent() const
{
    return currentlifePoints_/maxlifePoints_ * 100;
}

void Enemy::decreaseLife(int damage_)
{
    currentlifePoints_-=damage_;
}