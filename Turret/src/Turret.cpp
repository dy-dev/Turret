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
};

Quadrant getQuadrant(float orientation);


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
        screenWidth / 2 - playerTurret.centerRotation.x ,
        screenHeight / 2 - playerTurret.centerRotation.y ,
        playerTurret.texture.width ,playerTurret.texture.height
    };

    /*
    * Shot initialisation
    */
    Shot shot = { playerTurret.position,
                        { },
                        8.f,
                        LoadTexture("./assets/textures/Shot.png"),
                        false };
    Rectangle sourceShotTextRectangle = { 0,0,shot.texture.width ,shot.texture.height };
    Rectangle destShotRectangle;

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

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !shot.fired)
        {
            shot.direction = Vector2Normalize(turretToMouse);
            shot.position = Vector2Add(playerTurret.position,
                Vector2Scale(shot.direction, playerTurret.texture.width * .7f)
            );
            destShotRectangle = { shot.position.x - shot.texture.width / 2.f, shot.position.y - shot.texture.height / 2.f, (float)shot.texture.width * 0.75f, (float)shot.texture.height * 0.75f };
            shot.fired = true;
            Quadrant destinationQuadrant = getQuadrant(playerTurret.orientation);
            switch (destinationQuadrant)
            {
            case Quadrant::NE:
                shot.tint = RED;
                break;
            case Quadrant::SE:
                shot.tint = GREEN;
                break;
            case Quadrant::SW:
                shot.tint = BLUE;
                break;
            case Quadrant::NW:
                shot.tint = WHITE;
                break;
            default:
                break;
            }
        }

        if (shot.fired)
        {
            destShotRectangle.x += shot.direction.x * shot.speed;
            destShotRectangle.y += shot.direction.y * shot.speed;
            DrawTexturePro(shot.texture, sourceShotTextRectangle, destShotRectangle,
                { shot.texture.width * 0.75f / 2.f,shot.texture.height * 0.75f / 2.f }, 
                0, shot.tint);

            if (destShotRectangle.x > screenWidth + shot.texture.width / 2 ||
                destShotRectangle.x <-shot.texture.width / 2 ||
                destShotRectangle.y > screenHeight + shot.texture.height / 2 ||
                destShotRectangle.y < -shot.texture.height / 2)
            {
                shot.fired = false;
            }
        }

        DrawTexturePro(playerTurret.texture, sourcePlayerTextRectangle, destPlayerTextRectangle,
            playerTurret.centerRotation, playerTurret.orientation, WHITE);

        DrawText(colorstream.str().c_str(), 190, 250, 20, LIGHTGRAY);
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