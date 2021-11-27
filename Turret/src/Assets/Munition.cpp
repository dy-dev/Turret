#include "raylib.h"
#include "raymath.h"
#include "Assets/Munition.h"
#include "Enemies/Enemy.h"
#include "Game/GameManager.h"
#include "Game/Utilities.h"
#include "Player/Player.h"


Munition::Munition(Vector2 p_Position, const int p_iScreenWidth, const int p_iScreenHeight, const char* p_pcTexturePath)
    : MovableObjects(p_Position, p_iScreenWidth, p_iScreenHeight, p_pcTexturePath, {})
    , GraphicObjects(p_Position, p_iScreenWidth, p_iScreenHeight, p_pcTexturePath)
    , Destroyable{ false }
    /* m_fSpeed{ 4.f }
    , m_Texture{ LoadTexture("./assets/textures/Shot.png") }
    , m_SourceRectangle{ 0,0,(float)m_Texture.width ,(float)m_Texture.height }
    , m_DestRectangle{  }
    , m_BoundingRectangle{}      */
    , m_bFired{ false }
    , m_fScaleFactor{ 0.7f }
    , m_fTargetWidth{ m_Texture.width * m_fScaleFactor }
    , m_fTargetHeight{ m_Texture.height * m_fScaleFactor }
    , m_Owner{  }
{

}

Munition::Munition(GraphicObjects* p_Owner)
    : Munition{ p_Owner->getPosition(),0,0,"./assets/textures/Shot.png" }
{
    m_Owner = p_Owner;
}

void Munition::fire(Vector2 p_PlayerDirection)
{
    m_Direction = Vector2Normalize(p_PlayerDirection);
    m_Position = Vector2Add({ m_Owner->getPosition().x - m_fTargetWidth / 2.f,
            m_Owner->getPosition().y - m_fTargetHeight / 2.f },
        Vector2Scale(m_Direction, m_Owner->getTexture().width * 0.6f)
    );

    m_DestinationRectangle = calculateDestinationRectangle(m_Position, { m_fTargetWidth / 2.f ,  m_fTargetHeight / 2.f }, m_Texture, m_fScaleFactor);

    m_BoundingRectangle = m_DestinationRectangle;
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


void Munition::update(GraphicObjects*** p_EnemyArray, int* p_EnemyByColorArray)
{
    if (m_bFired)
    {
        m_DestinationRectangle.x += m_Direction.x * m_fSpeed;
        m_DestinationRectangle.y += m_Direction.y * m_fSpeed;
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
        DrawTexturePro(m_Texture, m_SourceRectangle, m_DestinationRectangle, { m_fTargetWidth / 2.f, m_fTargetHeight / 2.f }, 0, m_Tint);
        DrawRectangleLines(m_BoundingRectangle.x, m_BoundingRectangle.y, m_BoundingRectangle.width, m_BoundingRectangle.height, YELLOW);
        DrawRectangleLines(m_DestinationRectangle.x, m_DestinationRectangle.y, m_DestinationRectangle.width, m_DestinationRectangle.height, GREEN);
        //GraphicObjects::draw();
    }
}

void Munition::reset()
{
    //m_Position = m_Owner->getPosition();
    m_bFired = false;

}
