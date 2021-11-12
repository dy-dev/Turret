// Turret.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Utilities.h"
#include "Utils.h"
#include "raylib.h"
#include "raymath.h"

#include "GameManager.h"


  /*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <sstream>

//
//
//struct Shot
//{
//    Vector2 m_position;         //Coordinate of the player in the window coordinate system
//    Vector2 direction;  //Coordinates of the rotation center in the image coordinate system
//    float speed;
//    Texture2D texture;
//    bool fired;
//    Color tint;
//    Rectangle destRectangle;
//    Rectangle boundingRectangle;
//};
//
//
//struct Enemy
//{
//    Vector2 m_position;
//    Vector2 direction;
//    float speed;
//    Texture2D backTexture;
//    Texture2D frontTexture;
//    Color tint;
//    bool destroyed;
//    float orientation;
//    Vector2 centerRotation;
//    Rectangle destRectangle;
//    Rectangle boundingRectangle;
//};

/**
* Function declation
*/
//Quadrant getQuadrant(float orientation);
//
//void checkCollision(Shot* munitions, Enemy* enemies);
//Rectangle getDestinationRectangle(Vector2 pos, Vector2 origin, Texture2D texture, float scaleFactor);

/**
* globale Variables declaration
*/
const int nbShots = 30;
const int nbEnemies = 10;


bool gameover = false;


//
//void changeTint(const char* pointerToEnemy)
//{
//    char* end;
//    unsigned long long enemyAdress = strtoull(pointerToEnemy, &end, 16);
//    Enemy* enemy = (Enemy*)enemyAdress;
//    enemy->tint = BLACK;
//}


int main(int argc, char** argv)
{
  

    std::stringstream outstream;
    // outstream << "You want to fight " << enemies << " enemies !!";
    std::stringstream colorstream;



    GameManager* gm = new GameManager();
    gm->setup(argv[1]);
    gm->runGame();

    return 0;
}

