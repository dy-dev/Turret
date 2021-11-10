// Turret.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Utilities.h"
#include "Utils.h"
#include "raylib.h"
#include "raymath.h"

#include "Player.h"


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
    Vector2 m_position;         //Coordinate of the player in the window coordinate system
    Vector2 centerRotation;  //Coordinates of the rotation center in the image coordinate system
    float orientation;
    Texture2D texture;
};


struct Shot
{
    Vector2 m_position;         //Coordinate of the player in the window coordinate system
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
    Vector2 m_position;
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


bool gameover = false;



void changeTint(const char* pointerToEnemy)
{
    char* end;
    unsigned long long enemyAdress = strtoull(pointerToEnemy, &end, 16);
    Enemy* enemy = (Enemy*)enemyAdress;
    enemy->tint = BLACK;
}


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
    /* Shot shot = { playerTurret.m_position,
                         { },
                         8.f,
                         LoadTexture("./assets/textures/Shot.png"),
                         false };
     Rectangle sourceShotTextRectangle = { 0,0,shot.texture.width ,shot.texture.height };
     Rectangle destShotRectangle;*/

    Shot playerShots[nbShots];

    for (size_t i = 0; i < nbShots; i++)
    {
        playerShots[i] = { playerTurret.m_position,
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
    const int nbColors = 4;
    Enemy* coloredEnemies[nbColors];
    int nbEnemybyColor[nbColors];
    for (size_t i = 0; i < nbColors; i++)
    {
        char* color = nullptr;
        Color c = WHITE;
        switch (i)
        {
        case 0:
            color = new char[] {"Red"};
            c = RED;
            break;
        case 1:
            color = new char[] {"Green"};
            c = GREEN;
            break;
        case 2:
            color = new char[] {"Blue"};
            c = BLUE;
            break;
        case 3:
            color = new char[] {"White"};
            c = WHITE;
            break;
        default:
            break;
        }
        nbEnemybyColor[i] = selectEnemyNumber(color);
        coloredEnemies[i] = new Enemy[nbEnemybyColor[i]];
        for (size_t j = 0; j < nbEnemybyColor[i]; j++)
        {
            coloredEnemies[i][j] = {
                {(float)GetRandomValue(100, screenWidth - 100),(float)GetRandomValue(100, screenHeight - 100)},
                Vector2Normalize({(float)GetRandomValue(-100, 100), (float)GetRandomValue(-100, 100)}),
                1.f,
                LoadTexture("./assets/textures/Enemy.png"),
                LoadTexture("./assets/textures/Enemy_color.png"),
                c,
                false
            };

            coloredEnemies[i][j].centerRotation = { coloredEnemies[i][j].backTexture.width / 2.f,
                                   coloredEnemies[i][j].backTexture.height / 2.f };

            coloredEnemies[i][j].destRectangle = getDestinationRectangle(coloredEnemies[i][j].m_position,

                coloredEnemies[i][j].centerRotation, coloredEnemies[i][j].backTexture, 1.f);

            coloredEnemies[i][j].boundingRectangle = coloredEnemies[i][j].destRectangle;
            coloredEnemies[i][j].boundingRectangle.x -= coloredEnemies[i][j].centerRotation.x;
            coloredEnemies[i][j].boundingRectangle.y -= coloredEnemies[i][j].centerRotation.y;
            coloredEnemies[i][j].orientation = Vector2Angle({}, coloredEnemies[i][j].direction);
        }

        delete[] color;
    }


    //Enemy enemies[nbEnemies];

    //for (size_t i = 0; i < nbEnemies; i++)
    //{
    //    enemies[i] = {
    //        {(float)GetRandomValue(100, screenWidth - 100),(float)GetRandomValue(100, screenHeight - 100)},
    //        Vector2Normalize({(float)GetRandomValue(-100, 100), (float)GetRandomValue(-100, 100)}),
    //        1.f,
    //        LoadTexture("./assets/textures/Enemy.png"),
    //        LoadTexture("./assets/textures/Enemy_color.png"),
    //        {(unsigned char)GetRandomValue(0, 255),
    //        (unsigned char)GetRandomValue(0, 255),
    //        (unsigned char)GetRandomValue(0, 255),
    //        255 },
    //        false
    //    };

    //    enemies[i].centerRotation = { enemies[i].backTexture.width / 2.f,
    //                                enemies[i].backTexture.height / 2.f };

    //    enemies[i].destRectangle = getDestinationRectangle(enemies[i].m_position,

    //        enemies[i].centerRotation, enemies[i].backTexture, 1.f);

    //    enemies[i].boundingRectangle = enemies[i].destRectangle;
    //    enemies[i].boundingRectangle.x -= enemies[i].centerRotation.x;
    //    enemies[i].boundingRectangle.y -= enemies[i].centerRotation.y;

    //    enemies[i].orientation = Vector2Angle({}, enemies[i].direction);
    //}
    Rectangle sourceEnemmyTextRectangle = { 0,0,coloredEnemies[0][0].backTexture.width ,coloredEnemies[0][0].backTexture.height };


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

        if (!gameover)
        {
            Vector2 mousePosition = GetMousePosition();
            Vector2 turretToMouse = Vector2Subtract(mousePosition, playerTurret.m_position);
            playerTurret.orientation = Vector2Angle({}, turretToMouse);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                for (int i = 0; i < nbColors; i++)
                {
                    if (coloredEnemies[i] == nullptr)
                        continue;

                    int j = -1;
                    while (++j < nbEnemybyColor[i])
                    {
                        if (coloredEnemies[i][j].destroyed)
                            continue;

                        if (CheckCollisionPointRec(GetMousePosition(), coloredEnemies[i][j].boundingRectangle))
                        {
                            unsigned long long adress = (unsigned long long) & (coloredEnemies[i][j]);
                            char buf[24];
                            sprintf_s(buf, "%llX", adress);
                            changeTint(buf);
                            goto jumpToEndIf;
                        }
                    }
                }
                //for (Shot shot : playerShots)
                for (size_t i = 0; i < nbShots; i++)
                {
                    if (!playerShots[i].fired)
                    {
                        playerShots[i].direction = Vector2Normalize(turretToMouse);
                        playerShots[i].m_position =
                            Vector2Add(
                                { playerTurret.m_position.x - targetWidth / 2.f,
                                 playerTurret.m_position.y - targetHeight / 2.f },
                                Vector2Scale(playerShots[i].direction, playerTurret.texture.width * .6f)
                            );

                        playerShots[i].destRectangle = getDestinationRectangle(playerShots[i].m_position,

                            { targetWidth / 2.f ,  targetHeight / 2.f },
                            playerShots[i].texture, shotScaleFactor);
                        /* {
                        playerShots[i].m_position.x + targetWidth / 2.f,
                        playerShots[i].m_position.y + targetHeight / 2.f,
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
        jumpToEndIf:
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

            for (size_t i = 0; i < nbColors; i++)
            {
                checkCollision(playerShots, coloredEnemies[i]);
            }
            int colorsDestroyed = 1;
            for (int i = 0; i < nbColors; i++)
            {
                int j = -1;
                int nbDestroyed = 1;
                if (coloredEnemies[i] == nullptr) {
                    colorsDestroyed++;
                    continue;
                }

                while (++j < nbEnemybyColor[i])
                {
                    if (coloredEnemies[i][j].destroyed)
                    {
                        nbDestroyed++;
                        continue;
                    }

                    coloredEnemies[i][j].destRectangle.x += coloredEnemies[i][j].direction.x * coloredEnemies[i][j].speed;
                    coloredEnemies[i][j].destRectangle.y += coloredEnemies[i][j].direction.y * coloredEnemies[i][j].speed;
                    coloredEnemies[i][j].boundingRectangle.x += coloredEnemies[i][j].direction.x * coloredEnemies[i][j].speed;
                    coloredEnemies[i][j].boundingRectangle.y += coloredEnemies[i][j].direction.y * coloredEnemies[i][j].speed;

                    bool modif = false;
                    //If enemies goes to far on the left or right  of the window
                    if (coloredEnemies[i][j].destRectangle.x - coloredEnemies[i][j].centerRotation.x< 0 ||
                        coloredEnemies[i][j].destRectangle.x + coloredEnemies[i][j].backTexture.width - coloredEnemies[i][j].centerRotation.x> screenWidth)
                    {
                        coloredEnemies[i][j].direction.x *= -1;
                        modif = true;
                    }

                    if (coloredEnemies[i][j].destRectangle.y - coloredEnemies[i][j].centerRotation.y < 0 ||
                        coloredEnemies[i][j].destRectangle.y + coloredEnemies[i][j].backTexture.height - coloredEnemies[i][j].centerRotation.y > screenHeight)
                    {
                        coloredEnemies[i][j].direction.y *= -1;
                        modif = true;
                    }
                    if (modif)
                        coloredEnemies[i][j].orientation = Vector2Angle({}, coloredEnemies[i][j].direction);

                    DrawRectangleLines(coloredEnemies[i][j].boundingRectangle.x,
                        coloredEnemies[i][j].boundingRectangle.y,
                        coloredEnemies[i][j].boundingRectangle.width, coloredEnemies[i][j].boundingRectangle.height, GREEN);

                    DrawTexturePro(coloredEnemies[i][j].backTexture, sourceEnemmyTextRectangle,
                        coloredEnemies[i][j].destRectangle,
                        { coloredEnemies[i][j].backTexture.width / 2.f,
                        coloredEnemies[i][j].backTexture.height / 2.f },
                        coloredEnemies[i][j].orientation - 45, WHITE);
                    DrawTexturePro(coloredEnemies[i][j].frontTexture, sourceEnemmyTextRectangle,
                        coloredEnemies[i][j].destRectangle,
                        { coloredEnemies[i][j].frontTexture.width / 2.f,
                        coloredEnemies[i][j].frontTexture.height / 2.f },
                        coloredEnemies[i][j].orientation - 45, coloredEnemies[i][j].tint);
                }
                if (nbDestroyed == nbEnemybyColor[i])
                {
                    delete[] coloredEnemies[i];
                    coloredEnemies[i] = nullptr;
                }
            }
            if (colorsDestroyed == nbColors)
                gameover = true;
            DrawRectanglePro(destPlayerTextRectangle, playerTurret.centerRotation,
                playerTurret.orientation, RED);
            DrawTexturePro(playerTurret.texture, sourcePlayerTextRectangle, destPlayerTextRectangle,
                playerTurret.centerRotation, playerTurret.orientation, WHITE);


            DrawText(colorstream.str().c_str(), 190, 250, 20, LIGHTGRAY);
            DrawLine(screenWidth / 2, screenHeight / 2, mousePosition.x, mousePosition.y, GREEN);
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, GREEN);
            DrawLine(0, screenHeight / 2, screenWidth, screenHeight / 2, GREEN);
        }
        else
        {
            DrawText("GAME OVER", 190, 250, 90, LIGHTGRAY);

        }

        EndDrawing();
        //----------------------------------------------------------------------------------

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


Quadrant getQuadrant(float orientation)
{
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
                if (enemies != nullptr) {
                    Enemy& currentEnemy = *(enemies + j);
                    if (!currentEnemy.destroyed)
                    {
                        if (CheckCollisionRecs(munitions[i].boundingRectangle, currentEnemy.boundingRectangle) &&
                            ColorToInt(currentEnemy.tint) == ColorToInt(munitions[i].tint))
                        {
                            munitions[i].fired = false;
                            currentEnemy.destroyed = true;
                        }
                    }
                }
            }
        }
    }
}

