#pragma once
#include "Game/MovableObjects.h"
#include "Game/Destroyable.h"

class Munition : virtual public MovableObjects, public Destroyable {
public:
    Munition(class GraphicObjects* p_Owner);
    Munition(Vector2 p_Position, const int p_iScreenWidth, const int p_iScreenHeight, const char* p_pcTexturePath);

    void fire(Vector2 p_PlayerDirection);
    void update(GraphicObjects*** p_EnemyArray, int* p_EnemyByColorArray);
    virtual void onClick() override {};

    void reset();

    void draw() override;
    
    bool getFired() { return m_bFired;}
    Color getColor() { return m_Tint; };


protected:
    GraphicObjects* m_Owner;
    bool m_bFired;
    Color m_Tint;
    float m_fScaleFactor;
    float m_fTargetWidth;
    float m_fTargetHeight;
};

