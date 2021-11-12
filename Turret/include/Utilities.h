#pragma once
#include "raylib.h"

int howManyEnemies(void);

//Color exercise : Allow the user to enter a color and its decomposition displayed on
//the main window
unsigned int myconvert(char color[]);
unsigned int getColor();


unsigned char getRedVal(int color);
unsigned char getGreenVal(int color);
unsigned char getBlueVal(int color);

Rectangle getDestinationRectangle(Vector2 pos, Vector2 origin, Texture2D texture, float scaleFactor);
