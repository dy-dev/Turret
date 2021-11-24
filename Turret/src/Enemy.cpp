#include "raylib.h"
#include "raymath.h"
#include "Utilities.h"
#include "GameManager.h"
#include "Munition.h"
#include "Enemy.h"

Enemy::Enemy()
    : m_Position{ (float)GetRandomValue(100, GameManager::SCREEN_WIDTH - 100), (float)GetRandomValue(100, GameManager::SCREEN_HEIGHT - 100) }
    , m_Direction{ Vector2Normalize({ (float)GetRandomValue(-100, 100), (float)GetRandomValue(-100, 100) }) }
    , m_fSpeed{ 3.f }
    , m_FrontTexture{ LoadTexture("./assets/textures/Enemy.png") }
    , m_BackTexture{ LoadTexture("./assets/textures/Enemy_color.png") }
    , m_bDestroyed{ false }
    , m_CenterRotation{ m_BackTexture.width / 2.f, m_BackTexture.height / 2.f }
    , m_SourceRectangle{ 0,0, (float)m_BackTexture.width , (float)m_BackTexture.height }
    , m_DestRectangle{ getDestinationRectangle(m_Position, m_CenterRotation, m_BackTexture, 1.f) }
    , m_BoundingRectangle{ m_DestRectangle }
    , m_fOrientation{ Vector2Angle({}, m_Direction) }
    , m_Munition{new Munition(this)}
{

    m_BoundingRectangle.x -= m_CenterRotation.x;
    m_BoundingRectangle.y -= m_CenterRotation.y;
    
}

Enemy::~Enemy()
{
    delete m_Munition;
}

void Enemy::update()
{
    m_DestRectangle.x += m_Direction.x * m_fSpeed;
    m_DestRectangle.y += m_Direction.y * m_fSpeed;
    m_BoundingRectangle.x += m_Direction.x * m_fSpeed;
    m_BoundingRectangle.y += m_Direction.y * m_fSpeed;

    bool modif = false;
    //If enemies goes to far on the left or right  of the window
    if (m_DestRectangle.x - m_CenterRotation.x< 0 ||
        m_DestRectangle.x + m_BackTexture.width - m_CenterRotation.x> GameManager::SCREEN_WIDTH)
    {
        m_Direction.x *= -1;
        modif = true;
    }

    if (m_DestRectangle.y - m_CenterRotation.y < 0 ||
        m_DestRectangle.y + m_BackTexture.height - m_CenterRotation.y >  GameManager::SCREEN_HEIGHT)
    {
        m_Direction.y *= -1;
        modif = true;
    }
    if (modif)
        m_fOrientation = Vector2Angle({}, m_Direction);
}

void Enemy::draw()
{
    DrawRectangleLines(m_BoundingRectangle.x,
         m_BoundingRectangle.y,
         m_BoundingRectangle.width, m_BoundingRectangle.height, GREEN);

    DrawTexturePro(m_BackTexture, m_SourceRectangle,
        m_DestRectangle,
        { m_BackTexture.width / 2.f,
         m_BackTexture.height / 2.f },
        m_fOrientation - 45, WHITE);
    DrawTexturePro(m_FrontTexture, m_SourceRectangle,
        m_DestRectangle,
        { m_FrontTexture.width / 2.f,
        m_FrontTexture.height / 2.f },
        m_fOrientation - 45, m_Tint);
}
