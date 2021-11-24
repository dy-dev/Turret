#pragma once
//struct Vector2;
//struct Texture;
//struct Color;
//struct Rectangle;
class Enemy
{
public:
    Enemy();
    ~Enemy();
    Vector2 getPosition(){ return m_Position; }
    Vector2 getDirection() { return m_Direction; }
    float getSpeed() { return m_fSpeed; }
    Texture getBackTexture() { return m_BackTexture; }
    Texture getFrontTexture() { return m_FrontTexture; }
    Color getTint() { return m_Tint; }
    void setTint(int p_iColor) { m_Tint = GetColor(p_iColor); }
    bool getDestroyed() { return m_bDestroyed; }
    void setDestroyed(bool p_bDestroyed) { m_bDestroyed = p_bDestroyed; }
    float getOrientation() { return m_fOrientation; }
    Vector2 getCenterRotation() { return m_CenterRotation; }
    Rectangle getDestRectangle() { return m_DestRectangle; }
    Rectangle getBoundingRectangle() { return m_BoundingRectangle; }


    void update();
    void draw();

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
    Rectangle m_SourceRectangle;
    Rectangle m_DestRectangle;
    Rectangle m_BoundingRectangle;

    class Munition* m_Munition;
};

