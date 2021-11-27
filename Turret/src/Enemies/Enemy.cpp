#include "raylib.h"
#include "raymath.h"
#include "Game/Utilities.h"
#include "Game/GameManager.h"
#include "Assets/Munition.h"
#include "Enemies/Enemy.h"

Enemy::Enemy()
    :Enemy({ (float)GetRandomValue(100, GameManager::SCREEN_WIDTH - 100),
        (float)GetRandomValue(100, GameManager::SCREEN_HEIGHT - 100) } ,0,0, "./assets/textures/Enemy.png")
{

}

Enemy::Enemy(const Vector2& p_Position, const int p_iScreenWidth, const int p_iScreenHeight, const char* p_pcTexturePath)
    : GraphicObjects(p_Position, p_iScreenWidth, p_iScreenHeight, p_pcTexturePath)
    , Destroyable{false}
    /*, m_Direction{ Vector2Normalize({ (float)GetRandomValue(-100, 100), (float)GetRandomValue(-100, 100) }) }
    , m_FrontTexture{ LoadTexture("./assets/textures/Enemy.png") }    */
    , m_BackTexture{ LoadTexture("./assets/textures/Enemy_color.png") }      
     /*
    , m_CenterRotation{ m_BackTexture.width / 2.f, m_BackTexture.height / 2.f }
    , m_SourceRectangle{ 0,0, (float)m_BackTexture.width , (float)m_BackTexture.height }
    , m_DestRectangle{ getDestinationRectangle(m_Position, m_CenterRotation, m_BackTexture, 1.f) }
    , m_BoundingRectangle{ m_DestRectangle }
    , m_fOrientation{ Vector2Angle({}, m_Direction) }   */
    , m_Munition{new Munition(this)}    
    , m_Tint{WHITE}    
{

    //m_DestinationRectangle = { calculateDestinationRectangle(p_Position, m_CenterRotation, m_Texture, 1.f) };
    m_BoundingRectangle.x -= m_CenterRotation.x;
    m_BoundingRectangle.y -= m_CenterRotation.y;
    
}

Enemy::~Enemy()
{
    delete m_Munition;
}

void Enemy::Attack()
{
}

