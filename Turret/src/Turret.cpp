// Turret.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Utilities.h"
#include "raylib.h"
#include "raymath.h"


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

/*
    Types definition
*/

enum class Quadrant {
    NE,
    SE,
    SW,
    NW
};


struct Turret
{
    Vector2 position;         //Coordinate of the player in the window coordinate system
    Vector2 centerRotation;  //Coordinates of the rotation center in the image coordinate system
    float orientation;
    Texture2D texture;
};


struct Shot
{
    Vector2 position;         //Coordinate of the player in the window coordinate system
    Vector2 direction;  //Coordinates of the rotation center in the image coordinate system
    float speed;
    Texture2D texture;
    bool fired;
    Color tint;
    Rectangle destRectangle;
    Rectangle boundingRectangle;
};


struct Enemy
{
    Vector2 position;
    Vector2 direction;
    float speed;
    Texture2D backTexture;
    Texture2D frontTexture;
    Color tint;
    bool destroyed;
    float orientation;
    Vector2 centerRotation;
    Rectangle destRectangle;
    Rectangle boundingRectangle;
};

/**
* Function declation
*/
Quadrant getQuadrant(float orientation);

void checkCollision(Shot* munitions, Enemy* enemies);
Rectangle getDestinationRectangle(Vector2 pos, Vector2 origin, Texture2D texture, float scaleFactor);

/**
* globale Variables declaration
*/
const int nbShots = 30;
const int nbEnemies = 10;


int main(int argc, char** argv)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    /*
    * Player initialisation
    */
    Turret playerTurret = { {screenWidth / 2,screenHeight / 2},
                            { },
                            0.f,
                            LoadTexture("./assets/textures/Player.png") };
    playerTurret.centerRotation = { playerTurret.texture.height / 2.f,
                                    playerTurret.texture.height / 2.f };

    Rectangle sourcePlayerTextRectangle = { 0,0,playerTurret.texture.width ,playerTurret.texture.height };
    Rectangle destPlayerTextRectangle =
    {
        screenWidth / 2,
        screenHeight / 2,
        playerTurret.texture.width ,playerTurret.texture.height
    };

    /*
    * Shot initialisation
    */
    /* Shot shot = { playerTurret.position,
                         { },
                         8.f,
                         LoadTexture("./assets/textures/Shot.png"),
                         false };
     Rectangle sourceShotTextRectangle = { 0,0,shot.texture.width ,shot.texture.height };
     Rectangle destShotRectangle;*/

    Shot playerShots[nbShots];

    for (size_t i = 0; i < nbShots; i++)
    {
        playerShots[i] = { playerTurret.position,
                         { },
                         1.f,
                         LoadTexture("./assets/textures/Shot.png"),
                         false };
    }
    //Source rectangle is the same for all shots since they all sharing the same texture
    Rectangle sourceShotTextRectangle = { 0,0,playerShots[0].texture.width ,playerShots[0].texture.height };
    float shotScaleFactor = 0.7f;
    float targetWidth = (float)playerShots[0].texture.width * shotScaleFactor;
    float targetHeight = (float)playerShots[0].texture.height * shotScaleFactor;


    /**
    * Enemies initialisation
    */

    Enemy enemies[nbEnemies];

    for (size_t i = 0; i < nbEnemies; i++)
    {
        enemies[i] = {
            {(float)GetRandomValue(100, screenWidth - 100),(float)GetRandomValue(100, screenHeight - 100)},
            Vector2Normalize({(float)GetRandomValue(-100, 100), (float)GetRandomValue(-100, 100)}),
            1.f,
            LoadTexture("./assets/textures/Enemy.png"),
            LoadTexture("./assets/textures/Enemy_color.png"),
            {(unsigned char)GetRandomValue(0, 255),
            (unsigned char)GetRandomValue(0, 255),
            (unsigned char)GetRandomValue(0, 255),
            255 },
            false
        };

        enemies[i].centerRotation = { enemies[i].backTexture.width / 2.f,
                                    enemies[i].backTexture.height / 2.f };

        enemies[i].destRectangle = getDestinationRectangle(enemies[i].position,

            enemies[i].centerRotation, enemies[i].backTexture, 1.f);

        enemies[i].boundingRectangle = enemies[i].destRectangle;
        enemies[i].boundingRectangle.x -= enemies[i].centerRotation.x;
        enemies[i].boundingRectangle.y -= enemies[i].centerRotation.y;

        enemies[i].orientation = Vector2Angle({}, enemies[i].direction);
    }
    Rectangle sourceEnemmyTextRectangle = { 0,0,enemies[0].backTexture.width ,
        enemies[0].backTexture.height };


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    unsigned int passedColor = myconvert(argv[1]);
    Color  backgroundColor = { getRedVal(passedColor),
                                getGreenVal(passedColor),
                                getBlueVal(passedColor),
                                255 };

    std::stringstream outstream;
    // outstream << "You want to fight " << enemies << " enemies !!";
    std::stringstream colorstream;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(backgroundColor);

        Vector2 mousePosition = GetMousePosition();
        Vector2 turretToMouse = Vector2Subtract(mousePosition, playerTurret.position);
        playerTurret.orientation = Vector2Angle({}, turretToMouse);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            //for (Shot shot : playerShots)
            for (size_t i = 0; i < nbShots; i++)
            {
                if (!playerShots[i].fired)
                {
                    playerShots[i].direction = Vector2Normalize(turretToMouse);
                    playerShots[i].position =
                        Vector2Add(
                            { playerTurret.position.x - targetWidth / 2.f,
                             playerTurret.position.y - targetHeight / 2.f },
                            Vector2Scale(playerShots[i].direction, playerTurret.texture.width * .6f)
                        );

                    playerShots[i].destRectangle = getDestinationRectangle(playerShots[i].position,

                        { targetWidth / 2.f ,  targetHeight / 2.f },
                        playerShots[i].texture, shotScaleFactor);
                        /* {
                        playerShots[i].position.x + targetWidth / 2.f,
                        playerShots[i].position.y + targetHeight / 2.f,
                        targetWidth, targetHeight }*/

                    playerShots[i].boundingRectangle = playerShots[i].destRectangle;
                    playerShots[i].boundingRectangle.x -= targetWidth / 2.f;
                    playerShots[i].boundingRectangle.y -= targetHeight / 2.f;
                    Quadrant destinationQuadrant = getQuadrant(playerTurret.orientation);
                    switch (destinationQuadrant)
                    {
                    case Quadrant::NE:
                        playerShots[i].tint = RED;
                        break;
                    case Quadrant::SE:
                        playerShots[i].tint = GREEN;
                        break;
                    case Quadrant::SW:
                        playerShots[i].tint = BLUE;
                        break;
                    case Quadrant::NW:
                        playerShots[i].tint = WHITE;
                        break;
                    default:
                        break;
                    }
                    playerShots[i].fired = true;
                    break;
                }
            }
        }
        for (size_t i = 0; i < nbShots; i++)
        {
            if (playerShots[i].fired)
            {
                playerShots[i].destRectangle.x += playerShots[i].direction.x * playerShots[i].speed;
                playerShots[i].destRectangle.y += playerShots[i].direction.y * playerShots[i].speed;
                playerShots[i].boundingRectangle.x += playerShots[i].direction.x * playerShots[i].speed;
                playerShots[i].boundingRectangle.y += playerShots[i].direction.y * playerShots[i].speed;

                DrawTexturePro(playerShots[i].texture, sourceShotTextRectangle,
                    playerShots[i].destRectangle,
                    { targetWidth / 2.f, targetHeight / 2.f },
                    0, playerShots[i].tint);
                DrawRectangleLines(playerShots[i].boundingRectangle.x,
                    playerShots[i].boundingRectangle.y,
                    playerShots[i].boundingRectangle.width, playerShots[i].boundingRectangle.height, YELLOW);
                DrawRectangleLines(playerShots[i].destRectangle.x,
                    playerShots[i].destRectangle.y,
                    playerShots[i].destRectangle.width, playerShots[i].destRectangle.height, GREEN);

                if (playerShots[i].boundingRectangle.x > screenWidth + playerShots[i].texture.width / 2 ||
                    playerShots[i].boundingRectangle.x <-playerShots[i].texture.width / 2 ||
                    playerShots[i].boundingRectangle.y > screenHeight + playerShots[i].texture.height / 2 ||
                    playerShots[i].boundingRectangle.y < -playerShots[i].texture.height / 2)
                {
                    playerShots[i].fired = false;
                }
            }
        }

        checkCollision(playerShots, enemies);
        int i = -1;
        while (++i < nbEnemies)
        {
            if (enemies[i].destroyed)
                continue;

            enemies[i].destRectangle.x += enemies[i].direction.x * enemies[i].speed;
            enemies[i].destRectangle.y += enemies[i].direction.y * enemies[i].speed;
            enemies[i].boundingRectangle.x += enemies[i].direction.x * enemies[i].speed;
            enemies[i].boundingRectangle.y += enemies[i].direction.y * enemies[i].speed;

            bool modif = false;
            //If enemies goes to far on the left or right  of the window
            if (enemies[i].destRectangle.x - enemies[i].centerRotation.x< 0 ||
                enemies[i].destRectangle.x + enemies[i].backTexture.width - enemies[i].centerRotation.x> screenWidth)
            {
                enemies[i].direction.x *= -1;
                modif = true;
            }

            if (enemies[i].destRectangle.y - enemies[i].centerRotation.y < 0 ||
                enemies[i].destRectangle.y + enemies[i].backTexture.height - enemies[i].centerRotation.y > screenHeight)
            {
                enemies[i].direction.y *= -1;
                modif = true;
            }
            if (modif)
                enemies[i].orientation = Vector2Angle({}, enemies[i].direction);

            DrawRectangleLines(enemies[i].boundingRectangle.x,
                enemies[i].boundingRectangle.y,
                enemies[i].boundingRectangle.width, enemies[i].boundingRectangle.height, GREEN);

            DrawTexturePro(enemies[i].backTexture, sourceEnemmyTextRectangle,
                enemies[i].destRectangle,
                { enemies[i].backTexture.width / 2.f,
                enemies[i].backTexture.height / 2.f },
                enemies[i].orientation - 45, WHITE);
            DrawTexturePro(enemies[i].frontTexture, sourceEnemmyTextRectangle,
                enemies[i].destRectangle,
                { enemies[i].frontTexture.width / 2.f,
                enemies[i].frontTexture.height / 2.f },
                enemies[i].orientation - 45, enemies[i].tint);
        }
        DrawRectanglePro(destPlayerTextRectangle, playerTurret.centerRotation,
            playerTurret.orientation, RED);
        DrawTexturePro(playerTurret.texture, sourcePlayerTextRectangle, destPlayerTextRectangle,
            playerTurret.centerRotation, playerTurret.orientation, WHITE);


        DrawText(colorstream.str().c_str(), 190, 250, 20, LIGHTGRAY);
        DrawLine(screenWidth / 2, screenHeight / 2, mousePosition.x, mousePosition.y, GREEN);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, GREEN);
        DrawLine(0, screenHeight / 2, screenWidth, screenHeight / 2, GREEN);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


Quadrant getQuadrant(float orientation) {
    if (orientation >= 0 && orientation < 90)
        return Quadrant::SE;
    else if (orientation >= 90 && orientation < 180)
        return Quadrant::SW;
    else if (orientation >= 180 && orientation < 270)
        return Quadrant::NW;
    else
        return Quadrant::NE;

    return Quadrant::NE;
}

Rectangle getDestinationRectangle(Vector2 pos, Vector2 origin, Texture2D texture, float scaleFactor)
{
    return {
        pos.x + origin.x,
        pos.y + origin.y,
        (float)texture.width * scaleFactor, (float)texture.height * scaleFactor };
}


void checkCollision(Shot* munitions, Enemy* enemies)
{
    for (size_t i = 0; i < nbShots; i++)
    {
        if (munitions[i].fired)
        {
            for (size_t j = 0; j < nbEnemies; j++)
            {
                Enemy& currentEnemy = *(enemies + j);
                if (!currentEnemy.destroyed)
                {
                    if (CheckCollisionRecs(munitions[i].boundingRectangle, currentEnemy.boundingRectangle))
                    {
                        munitions[i].fired = false;
                        currentEnemy.destroyed = true;
                    }
                }
            }
        }
    }
}
