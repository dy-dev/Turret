#pragma once

class Player
{
public:
    Vector2 getPosition() { return m_Position; }         //Coordinate of the player in the window coordinate system
    Vector2 getCenterRotation() { return m_CenterRotation; }  //Coordinates of the rotation center in the image coordinate system
    float getOrientation() { return m_fOrientation; }
    Texture2D getTexture() { return m_Texture; }
    
    void turn();
    class Munition* shoot();

private:
    Munition* m_ShotsArray;

    Vector2 m_Position;         //Coordinate of the player in the window coordinate system
    Vector2 m_CenterRotation;  //Coordinates of the rotation center in the image coordinate system
    float m_fOrientation;
    Texture2D m_Texture;
};
