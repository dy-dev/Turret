#pragma once
#include "raylib.h"

/*
    Types definition
*/

enum class Quadrant {
    NE,
    SE,
    SW,
    NW
};

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
    static const int NB_COLOR = 4;
public:
    GameManager();
    void setup(char* p_pcBackgroundColorAsText);
    void runGame();
private:
    void initEnemies();

    class Player* m_Player{};
    class Enemy** m_EnemiesArray;
    Color  m_BackgroundColor;

    int m_iNbEnemybyColorArray[NB_COLOR];
    bool m_bGameOver;
};