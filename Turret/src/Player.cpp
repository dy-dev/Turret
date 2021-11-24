#include "raylib.h"
#include "raymath.h"
#include "Munition.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Player.h"


Player::Player(Vector2 p_Position, const int p_iScreenWidth, const int p_iScreenHeight, const char* p_pcTexturePath)
    : m_Position{ p_Position }
    , m_Texture{ LoadTexture(p_pcTexturePath) }
    , m_fOrientation{}
    , m_CenterRotation{ m_Texture.height / 2.f, m_Texture.height / 2.f }
    , m_SourceRectangle{ 0,0,(float)m_Texture.width ,(float)m_Texture.height }
    , m_DestinationRectangle{ p_iScreenWidth / 2.f, p_iScreenHeight / 2.f,
                    (float)m_Texture.width , (float)m_Texture.height }
    , m_ShotsArray{ new Munition*[GameManager::NB_SHOTS] }
{
   
    for (size_t i = 0; i < GameManager::NB_SHOTS; i++)
    {
        m_ShotsArray[i] = new Munition(this);
    }
}

Player::~Player()
{
    for (size_t i = 0; i < GameManager::NB_SHOTS; i++)
    {
        delete m_ShotsArray[i];
    }
    delete[] m_ShotsArray;
}

Vector2 Player::update(Enemy** m_EnemiesArray, int* p_EnemyByColorArray)
{
    Vector2 mousePosition = GetMousePosition();
    Vector2 turretToMouse = Vector2Subtract(mousePosition, m_Position);
    m_fOrientation = Vector2Angle({}, turretToMouse);
    for (size_t i = 0; i < GameManager::NB_SHOTS; i++)
        m_ShotsArray[i]->update(m_EnemiesArray, p_EnemyByColorArray);

    return turretToMouse;
}

void Player::draw()
{
    for (size_t i = 0; i < GameManager::NB_SHOTS; i++)
        m_ShotsArray[i]->draw();

    DrawRectanglePro(m_DestinationRectangle, m_CenterRotation, m_fOrientation, RED);
    DrawTexturePro(m_Texture, m_SourceRectangle, m_DestinationRectangle, m_CenterRotation, m_fOrientation, WHITE);
}

void Player::turn()
{
}

void Player::shoot(Vector2 p_PlayerDirection)
{
    for (size_t i = 0; i < GameManager::NB_SHOTS; i++)
        if (!m_ShotsArray[i]->getFired()) {
            m_ShotsArray[i]->fire(p_PlayerDirection);
            break;
        }
}

