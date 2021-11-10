#pragma once
class Munition
{
public:
    Vector2 getPosition() { return m_Position; }
    Vector2 getDirection() { return m_Direction; }
    float getSpeed() { return m_fSpeed; }
    Texture2D getTexture() { return m_texture; }
    bool getFired() { return m_bFired; }
    Color getColor() { return m_Tint; }
    Rectangle getDestRectangle() { return m_DestRectangle; }
    Rectangle getBoundingRectangle() { return m_BoundingRectangle; }


    void fire();
    void update(class Enemy* p_EnemyArray);

private:
    Vector2 m_Position;         //Coordinate of the player in the window coordinate system
    Vector2 m_Direction;  //Coordinates of the rotation center in the image coordinate system
    float m_fSpeed;
    Texture2D m_texture;
    bool m_bFired;
    Color m_Tint;
    Rectangle m_DestRectangle;
    Rectangle m_BoundingRectangle;
};

