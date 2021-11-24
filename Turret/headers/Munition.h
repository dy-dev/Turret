#pragma once
class Munition
{
public:
    Munition(class Player* p_Player);
    Munition(class Enemy* p_Enemy);

    Vector2 getPosition() { return m_Position; }
    Vector2 getDirection() { return m_Direction; }
    float getSpeed() { return m_fSpeed; }
    Texture2D getTexture() { return m_Texture; }
    bool getFired() { return m_bFired; }
    Color getColor() { return m_Tint; }
    Rectangle getDestRectangle() { return m_DestRectangle; }
    Rectangle getBoundingRectangle() { return m_BoundingRectangle; }


    void fire(Vector2 p_PlayerDirection);
    void update(Enemy** p_EnemyArray, int* p_EnemyByColorArray);
    void draw();
    void reset();

private:
    Munition();

    Player* m_Owner;
    Vector2 m_Position;         //Coordinate of the player in the window coordinate system
    Vector2 m_Direction;  //Coordinates of the rotation center in the image coordinate system
    float m_fSpeed;
    Texture2D m_Texture;
    bool m_bFired;
    Color m_Tint;
    Rectangle m_SourceRectangle;
    Rectangle m_DestRectangle;
    Rectangle m_BoundingRectangle;

    float m_fScaleFactor;
    float m_fTargetWidth;
    float m_fTargetHeight;
};

