#pragma once
//struct Vector2;
//struct Texture;
//struct Color;
//struct Rectangle;
class Enemy
{
    Vector2 getPosition(){ return m_Position; }
    Vector2 getDirection() { return m_Direction; }
    float getSpeed() { return m_fSpeed; }
    Texture getBackTexture() { return m_BackTexture; }
    Texture getFrontTexture() { return m_FrontTexture; }
    Color getTint() { return m_Tint; }
    bool getDestroyed() { return m_bDestroyed; }
    float getOrientation() { return m_fOrientation; }
    Vector2 getCenterRotation() { return m_CenterRotation; }
    Rectangle getDestRectangle() { return m_DestRectangle; }
    Rectangle getBoundingRectangle() { return m_BoundingRectangle; }


    void update();

private:
    Vector2 m_Position;
    Vector2 m_Direction;
    float m_fSpeed;
    Texture m_BackTexture;
    Texture m_FrontTexture;
    Color m_Tint;
    bool m_bDestroyed;
    float m_fOrientation;
    Vector2 m_CenterRotation;
    Rectangle m_DestRectangle;
    Rectangle m_BoundingRectangle;
};

