#include "raylib.h"
#include "raymath.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Player.h"
#include "Utilities.h"
#include "Munition.h"

Munition::Munition()
    : m_fSpeed{ 2.f }
    , m_Texture{ LoadTexture("./assets/textures/Shot.png") }
    , m_SourceRectangle{ 0,0,(float)m_Texture.width ,(float)m_Texture.height }
    , m_DestRectangle{  }
    , m_BoundingRectangle{}
    , m_bFired{ false }
    , m_fScaleFactor{ 0.7f }
    , m_fTargetWidth{ m_Texture.width * m_fScaleFactor }
    , m_fTargetHeight{ m_Texture.height * m_fScaleFactor }      
    , m_Owner{  }
    , m_Position{ }
{

}

Munition::Munition(Player* p_Player)
    : Munition{}
{
    m_Owner = p_Player;
    m_Position = m_Owner->getPosition() ;
}

Munition::Munition(Enemy* p_Enemy)
    :Munition{}
{
    m_Owner = nullptr;
    m_Position = p_Enemy->getPosition();
}

void Munition::fire(Vector2 p_PlayerDirection)
{
    m_Direction = Vector2Normalize(p_PlayerDirection);
    m_Position = Vector2Add({ m_Owner->getPosition().x - m_fTargetWidth / 2.f,
            m_Owner->getPosition().y - m_fTargetHeight / 2.f },
        Vector2Scale(m_Direction, m_Owner->getTexture().width * 0.6f)
    );

    m_DestRectangle = getDestinationRectangle(m_Position, { m_fTargetWidth / 2.f ,  m_fTargetHeight / 2.f }, m_Texture, m_fScaleFactor);


    m_BoundingRectangle = m_DestRectangle;
    m_BoundingRectangle.x -= m_fTargetWidth / 2.f;
    m_BoundingRectangle.y -= m_fTargetHeight / 2.f;
    Quadrant destinationQuadrant = getQuadrant(m_Owner->getOrientation());
    switch (destinationQuadrant)
    {
    case Quadrant::NE:
        m_Tint = RED;
        break;
    case Quadrant::SE:
        m_Tint = GREEN;
        break;
    case Quadrant::SW:
        m_Tint = BLUE;
        break;
    case Quadrant::NW:
        m_Tint = WHITE;
        break;
    default:
        break;
    }
    m_bFired = true;
}


void Munition::update(Enemy** p_EnemyArray, int* p_EnemyByColorArray)
{
    if (m_bFired)
    {
        m_DestRectangle.x += m_Direction.x * m_fSpeed;
        m_DestRectangle.y += m_Direction.y * m_fSpeed;
        m_BoundingRectangle.x += m_Direction.x * m_fSpeed;
        m_BoundingRectangle.y += m_Direction.y * m_fSpeed;

        if (m_BoundingRectangle.x > GameManager::SCREEN_WIDTH + m_Texture.width / 2 ||
            m_BoundingRectangle.x <-m_Texture.width / 2 ||
            m_BoundingRectangle.y > GameManager::SCREEN_HEIGHT + m_Texture.height / 2 ||
            m_BoundingRectangle.y < -m_Texture.height / 2)
        {
            m_bFired = false;
            return;
        }

        for (size_t i = 0; i < GameManager::NB_COLORS; i++)
        {
            if (p_EnemyArray[i])
            {
                checkCollision(this, p_EnemyArray[i], p_EnemyByColorArray[i]);
            }
        }
    }
}


void Munition::draw()
{
    if (m_bFired) {
        DrawTexturePro(m_Texture, m_SourceRectangle, m_DestRectangle, { m_fTargetWidth / 2.f, m_fTargetHeight / 2.f }, 0, m_Tint);
        DrawRectangleLines(m_BoundingRectangle.x, m_BoundingRectangle.y, m_BoundingRectangle.width, m_BoundingRectangle.height, YELLOW);
        DrawRectangleLines(m_DestRectangle.x, m_DestRectangle.y, m_DestRectangle.width, m_DestRectangle.height, GREEN);
    }
}

void Munition::reset()
{
    m_Position = m_Owner->getPosition();
    m_bFired = false;
}
