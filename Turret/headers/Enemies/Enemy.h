#pragma once
#include "Game/GraphicObjects.h"
#include "Game/Destroyable.h"
#include "Game/Shooter.h"

class Enemy : virtual public GraphicObjects, public Destroyable, public Shooter
{
public:
    Enemy();
    Enemy(const Vector2& p_Position, const int p_iScreenWidth, const int p_iScreenHeight, const char* p_pcTexturePath);
    ~Enemy() override;
   
    Texture getBackTexture() { return m_BackTexture; }
    Color getTint() { return m_Tint; }
    void setTint(int p_iColor) { m_Tint = GetColor(p_iColor); }
    
    void Attack();

protected:
    Texture m_BackTexture;
    Color m_Tint;
    class Munition* m_Munition;
};

