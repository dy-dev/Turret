#include "raylib.h"
#include "raymath.h"
#include "Assets/Munition.h"
#include "Enemies/Enemy.h"
#include "Game/GameManager.h"
#include "Player/Player.h"
#include "Assets/UpgradeBonus.h"



Player::Player(Vector2 p_Position, const int p_iScreenWidth, const int p_iScreenHeight, const char* p_pcTexturePath)
    : GraphicObjects(p_Position, p_iScreenWidth, p_iScreenHeight, p_pcTexturePath)
    , Destroyable{false}
    , m_ShotsArray{ new Munition*[GameManager::NB_SHOTS] }                
    , m_pGrapnel{}
{
    m_DestinationRectangle = { p_iScreenWidth / 2.f, p_iScreenHeight / 2.f, (float)m_Texture.width , (float)m_Texture.height };
        
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
     
void Player::update()
{
    GraphicObjects::update();
    //Enemy** m_EnemiesArray, int* p_EnemyByColorArray
    Vector2 mousePosition = GetMousePosition();
   /* m_Direction = Vector2Subtract(mousePosition, m_Position);*/
    m_fOrientation = Vector2Angle({}, Vector2Subtract(mousePosition, m_Position));
    for (size_t i = 0; i < GameManager::NB_SHOTS; i++)
        m_ShotsArray[i]->update(GameManager::getInstance().getEnemiesArray(),
            GameManager::getInstance().getNbEnemyBycolor());

}  

void Player::turn()
{
}

void Player::AddBonusToSlot()
{
}

void Player::draw()
{
    for (size_t i = 0; i < GameManager::NB_SHOTS; i++)
        m_ShotsArray[i]->draw();

    GraphicObjects::draw();
}


void Player::onClick()
{
    for (size_t i = 0; i < GameManager::NB_SHOTS; i++)
        if (!m_ShotsArray[i]->getFired()) {
            m_ShotsArray[i]->fire(Vector2Rotate({ 1,0 }, m_fOrientation));
            break;
        }
}

void Player::ShootGrapnel()
{

}

         