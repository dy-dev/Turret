#pragma once
#include "Game/MovableObjects.h"

class Grapnel : public MovableObjects {
public:
    Grapnel(Vector2 p_Position, const int p_iScreenWidth, const int p_iScreenHeight, const char* p_pcTexturePath);

    void TryGrabBonus(float p_fOrientation);
    void CalculateDirection();
    void Extends();
    void CatchBonus();
private:
    Vector2 m_Position;        //Coordinate of the player in the window coordinate system
    Vector2 m_Direction;       //Coordinates of the rotation center in the image coordinate system
    Texture2D m_TextureHook;
    Texture2D m_TextureCable;
    Rectangle m_SourceRectangle;
    Rectangle m_DestRectangle;
    bool m_bLaunched;
};

