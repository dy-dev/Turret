#include "raylib.h"
#include "raymath.h"
#include "Munition.h"
#include "Player.h"


Player::Player(Vector2 p_Position, const int p_iScreenWidth, const int p_iScreenHeight, const char* p_pcTexturePath)
    : m_Position{p_Position}
    , m_Texture{LoadTexture(p_pcTexturePath)}
    , m_fOrientation{}
    , m_CenterRotation { m_Texture.height / 2.f, m_Texture.height / 2.f }
    , m_SourceRectangle{ 0,0,(float)m_Texture.width ,(float)m_Texture.height }
    , m_DestinationRectangle{ p_iScreenWidth / 2.f, p_iScreenHeight / 2.f,
                    (float)m_Texture.width , (float)m_Texture.height }
{
   /* Turret playerTurret = { ,
                           { },
                           0.f,
                           LoadTexture("./assets/textures/Player.png") };
    playerTurret.centerRotation = { playerTurret.texture.height / 2.f,
                                    playerTurret.texture.height / 2.f };

    Rectangle sourcePlayerTextRectangle = 
    
    Rectangle destPlayerTextRectangle =
    {
        screenWidth / 2,
        screenHeight / 2,
        playerTurret.texture.width ,playerTurret.texture.height
    };

*/

}

void Player::update()
{
    Vector2 mousePosition = GetMousePosition();
    Vector2 turretToMouse = Vector2Subtract(mousePosition, m_Position);
    m_fOrientation = Vector2Angle({}, turretToMouse);
}

void Player::draw()
{
    DrawRectanglePro(m_DestinationRectangle,
        m_CenterRotation,
        m_fOrientation,
        RED);

    DrawTexturePro(m_Texture,
        m_SourceRectangle,
        m_DestinationRectangle,
        m_CenterRotation,
        m_fOrientation,
        WHITE);

}

void Player::turn()
{
}

Munition* Player::shoot()
{
    return nullptr;
}
