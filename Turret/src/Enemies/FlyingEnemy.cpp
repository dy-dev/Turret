
#include "Enemies/FlyingEnemy.h"
#include "Game/GameManager.h"

FlyingEnemy::FlyingEnemy()
    :FlyingEnemy(
        { (float)GetRandomValue(100, GameManager::SCREEN_WIDTH - 100),
        (float)GetRandomValue(100, GameManager::SCREEN_HEIGHT - 100) },
        0, 0, "./assets/textures/Enemy.png", {})
{

}

FlyingEnemy::FlyingEnemy(const Vector2& p_Position, const int p_iScreenWidth, 
    const int p_iScreenHeight, const char* p_pcTexturePath, const Vector2& p_Direction)
    : Enemy(p_Position, p_iScreenWidth, p_iScreenHeight, p_pcTexturePath)
    , MovableObjects(p_Position, p_iScreenWidth, p_iScreenHeight, p_pcTexturePath, p_Direction)
{

}
