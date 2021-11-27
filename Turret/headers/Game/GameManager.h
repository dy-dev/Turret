#pragma once
#include "raylib.h"

/*
    Types definition
*/


constexpr int getRaylibColor(Color color)
{
    return (((int)color.r << 24) | ((int)color.g << 16) | ((int)color.b << 8) | (int)color.a);
}

enum class ColorQuadrant {
    NE = getRaylibColor(RED),
    SE = getRaylibColor(GREEN),
    SW = getRaylibColor(BLUE),
    NW = getRaylibColor(WHITE)
};


class GameManager {
public :
    static const int SCREEN_HEIGHT = 840;
    static const int SCREEN_WIDTH = 1000;
    static const int NB_COLORS = 4;
    static const int NB_SHOTS = 10;
    
public:
    void setup(char* p_pcBackgroundColorAsText);
    void runGame();
    static GameManager& getInstance();
    class GraphicObjects*** getEnemiesArray() { return m_EnemiesArray; }
    int* getNbEnemyBycolor(){return m_iNbEnemybyColorArray;}

private:
    //Singleton Pattern implementation
    GameManager();
    static GameManager* s_GameManager;

    void manageButtonClick();
    void drawVisualAids();
    bool checkClickOnEnemy();
    bool manageEnemies(int& nbColorDestroyed);
    
    class Spawner* m_Spawner;

    GraphicObjects* m_Player;
    GraphicObjects*** m_EnemiesArray;
    
    Color  m_BackgroundColor;

    int* m_iNbEnemybyColorArray;
    bool m_bGameOver;
};