#pragma once
#include "raylib.h"


enum class Quadrant {
    NE,
    SE,
    SW,
    NW
};

int howManyEnemies(void);

//Color exercise : Allow the user to enter a color and its decomposition displayed on
//the main window
unsigned int myconvert(char color[]);
unsigned int getColor();

Quadrant getQuadrant(float orientation);

unsigned char getRedVal(int color);
unsigned char getGreenVal(int color);
unsigned char getBlueVal(int color);

void changeTint(const char* pointerToEnemy);

Rectangle calculateDestinationRectangle(Vector2 pos, Vector2 origin, Texture2D texture, float scaleFactor);

void checkCollision(class Munition* munitions, class GraphicObjects** enemies, int nbEnemies);
