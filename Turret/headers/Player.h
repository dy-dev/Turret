#pragma once

class Player
{
public:
    Player(Vector2 p_Position, const int p_iScreenWidth, const int p_iScreenHeight, const char* p_pcTexturePath);
    ~Player();
    Vector2 getPosition() { return m_Position; }         //Coordinate of the player in the window coordinate system
    Vector2 getCenterRotation() { return m_CenterRotation; }  //Coordinates of the rotation center in the image coordinate system
    float getOrientation() { return m_fOrientation; }
    Texture2D getTexture() { return m_Texture; }

    Rectangle getSourceRectangle() { return m_SourceRectangle; }
    Rectangle getDestinationRectangle() { return m_DestinationRectangle; }

    Vector2 update(class Enemy** m_EnemiesArray, int* p_EnemyByColorArray);
    void draw();
    void turn();
    void shoot(Vector2 p_PlayerDirection);

private:
    class Munition** m_ShotsArray;

    Vector2 m_Position;         //Coordinate of the player in the window coordinate system
    float m_fOrientation;
    Texture2D m_Texture;
    Vector2 m_CenterRotation;  //Coordinates of the rotation center in the image coordinate system
    Rectangle m_SourceRectangle;
    Rectangle m_DestinationRectangle;
};
