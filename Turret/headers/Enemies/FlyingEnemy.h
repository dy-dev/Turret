#pragma once
#include "Game/MovableObjects.h"
#include "Enemies/Enemy.h"

class FlyingEnemy : virtual public MovableObjects, virtual public Enemy {
public :
    FlyingEnemy();
    FlyingEnemy(const Vector2& p_Position, const int p_iScreenWidth, 
        const int p_iScreenHeight, const char* p_pcTexturePath, const Vector2& p_Direction);

};
