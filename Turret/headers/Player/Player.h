#pragma once

#include "Game/GraphicObjects.h"
#include "Game/Destroyable.h"
#include "Game/Shooter.h"
#include "Player/Grapnel.h"

class Player : public GraphicObjects, public Destroyable, public Shooter {
public:
    Player(Vector2 p_Position, const int p_iScreenWidth, const int p_iScreenHeight, const char* p_pcTexturePath);
    ~Player();

    virtual void draw() override;

    virtual void update() override;
    virtual void onClick() override;

    void shoot(Vector2 p_PlayerDirection);
    void ShootGrapnel();
    void turn();
    void AddBonusToSlot();
    
    bool getDestroyed() { return m_bDestroyed; };
    void setDestroyed(bool p_bDestroyed) { m_bDestroyed = p_bDestroyed; }

protected:
    class Munition** m_ShotsArray{};
    class Grapnel* m_pGrapnel{};
    bool m_bDestroyed{};
    int m_iLifePoints{};
    int m_iScore{};
};
