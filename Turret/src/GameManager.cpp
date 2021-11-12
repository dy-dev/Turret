#include "raylib.h"
#include "Enemy.h"
#include "Player.h"
#include "Utilities.h"
#include "GameManager.h"



GameManager::GameManager()
    : m_Player{ nullptr }
    , m_bGameOver{ false }
{
}

void GameManager::setup(char* p_pcBackgroundColorAsText)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    unsigned int passedColor = myconvert(p_pcBackgroundColorAsText);
    m_BackgroundColor = { getRedVal(passedColor),
                           getGreenVal(passedColor),
                           getBlueVal(passedColor),
                           255 };


    /*
     * Player initialisation
     */
    m_Player = new Player{ Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, SCREEN_WIDTH, SCREEN_HEIGHT, "./assets/textures/Player.png" };

    /**
    * Enemies initialisation
    */
    initEnemies();
}

void GameManager::runGame()
{
    int nbColorDestroyed = 0;
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
        ClearBackground(m_BackgroundColor);

        if (!m_bGameOver)
        {
            m_Player->update();
            m_Player->draw();



            for (int i = 0; i < NB_COLOR; i++) {
                int j = -1;
                int nbDestroyed = 1;
                if (m_EnemiesArray[i] == nullptr) {
                    nbColorDestroyed++;
                    continue;
                }


                while (++j < m_iNbEnemybyColorArray[i]) {
                    if (m_EnemiesArray[i][j].getDestroyed())
                    {
                        nbDestroyed++;
                        if (nbDestroyed == m_iNbEnemybyColorArray[i]) {
                            delete[] m_EnemiesArray[i];
                            m_EnemiesArray[i] = nullptr;
                        }
                        continue;
                    }
                    m_EnemiesArray[i][j].update();
                    m_EnemiesArray[i][j].draw();
                }

            }

            if (nbColorDestroyed == NB_COLOR)
                m_bGameOver = true;


            //DrawText(colorstream.str().c_str(), 190, 250, 20, LIGHTGRAY);
            DrawLine(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, GetMousePosition().x, GetMousePosition().y, GREEN);
            DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, GREEN);
            DrawLine(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, GREEN);



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
}

void GameManager::initEnemies()
{
    m_EnemiesArray = new Enemy * [NB_COLOR];

    for (size_t i = 0; i < NB_COLOR; i++)
    {
        m_iNbEnemybyColorArray[i] = GetRandomValue(1, 10);
        m_EnemiesArray[i] = new Enemy[m_iNbEnemybyColorArray[i]];
        Quadrant quadrant = (Quadrant)i;
        ColorQuadrant colorQuadrant;
        switch (quadrant)
        {
        case Quadrant::NE:
            colorQuadrant = ColorQuadrant::NE;
            break;
        case Quadrant::SE:
            colorQuadrant = ColorQuadrant::SE;
            break;
        case Quadrant::SW:
            colorQuadrant = ColorQuadrant::SW;
            break;
        case Quadrant::NW:
            colorQuadrant = ColorQuadrant::NW;
            break;
        default:
            break;
        }
        for (size_t j = 0; j < m_iNbEnemybyColorArray[i]; j++)
        {
            m_EnemiesArray[i][j].setTint((int)colorQuadrant);
        }
    }
}



//
///
//
//    /*
//    * Shot initialisation
//    */
//    /* Shot shot = { playerTurret.m_position,
//                         { },
//                         8.f,
//                         LoadTexture("./assets/textures/Shot.png"),
//                         false };
//     Rectangle sourceShotTextRectangle = { 0,0,shot.texture.width ,shot.texture.height };
//     Rectangle destShotRectangle;*/
//
//Shot playerShots[nbShots];
//
//for (size_t i = 0; i < nbShots; i++)
//{
//    playerShots[i] = { playerTurret.m_position,
//                     { },
//                     1.f,
//                     LoadTexture("./assets/textures/Shot.png"),
//                     false };
//}
////Source rectangle is the same for all shots since they all sharing the same texture
//Rectangle sourceShotTextRectangle = { 0,0,playerShots[0].texture.width ,playerShots[0].texture.height };
//float shotScaleFactor = 0.7f;
//float targetWidth = (float)playerShots[0].texture.width * shotScaleFactor;
//float targetHeight = (float)playerShots[0].texture.height * shotScaleFactor;
//
//





//    if (!gameover)
//    {
//        Vector2 mousePosition = GetMousePosition();
//        Vector2 turretToMouse = Vector2Subtract(mousePosition, playerTurret.m_position);
//        playerTurret.orientation = Vector2Angle({}, turretToMouse);
//
//        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
//        {
//            for (int i = 0; i < nbColors; i++)
//            {
//                if (coloredEnemies[i] == nullptr)
//                    continue;
//
//                int j = -1;
//                while (++j < nbEnemybyColor[i])
//                {
//                    if (coloredEnemies[i][j].destroyed)
//                        continue;
//
//                    if (CheckCollisionPointRec(GetMousePosition(), coloredEnemies[i][j].boundingRectangle))
//                    {
//                        unsigned long long adress = (unsigned long long) & (coloredEnemies[i][j]);
//                        char buf[24];
//                        sprintf_s(buf, "%llX", adress);
//                        changeTint(buf);
//                        goto jumpToEndIf;
//                    }
//                }
//            }
//            //for (Shot shot : playerShots)
//            for (size_t i = 0; i < nbShots; i++)
//            {
//                if (!playerShots[i].fired)
//                {
//                    playerShots[i].direction = Vector2Normalize(turretToMouse);
//                    playerShots[i].m_position =
//                        Vector2Add(
//                            { playerTurret.m_position.x - targetWidth / 2.f,
//                             playerTurret.m_position.y - targetHeight / 2.f },
//                            Vector2Scale(playerShots[i].direction, playerTurret.texture.width * .6f)
//                        );
//
//                    playerShots[i].destRectangle = getDestinationRectangle(playerShots[i].m_position,
//
//                        { targetWidth / 2.f ,  targetHeight / 2.f },
//                        playerShots[i].texture, shotScaleFactor);
//                    /* {
//                    playerShots[i].m_position.x + targetWidth / 2.f,
//                    playerShots[i].m_position.y + targetHeight / 2.f,
//                    targetWidth, targetHeight }*/
//
//                    playerShots[i].boundingRectangle = playerShots[i].destRectangle;
//                    playerShots[i].boundingRectangle.x -= targetWidth / 2.f;
//                    playerShots[i].boundingRectangle.y -= targetHeight / 2.f;
//                    Quadrant destinationQuadrant = getQuadrant(playerTurret.orientation);
//                    switch (destinationQuadrant)
//                    {
//                    case Quadrant::NE:
//                        playerShots[i].tint = RED;
//                        break;
//                    case Quadrant::SE:
//                        playerShots[i].tint = GREEN;
//                        break;
//                    case Quadrant::SW:
//                        playerShots[i].tint = BLUE;
//                        break;
//                    case Quadrant::NW:
//                        playerShots[i].tint = WHITE;
//                        break;
//                    default:
//                        break;
//                    }
//                    playerShots[i].fired = true;
//                    break;
//                }
//            }
//        }
//    jumpToEndIf:
//        for (size_t i = 0; i < nbShots; i++)
//        {
//            if (playerShots[i].fired)
//            {
//                playerShots[i].destRectangle.x += playerShots[i].direction.x * playerShots[i].speed;
//                playerShots[i].destRectangle.y += playerShots[i].direction.y * playerShots[i].speed;
//                playerShots[i].boundingRectangle.x += playerShots[i].direction.x * playerShots[i].speed;
//                playerShots[i].boundingRectangle.y += playerShots[i].direction.y * playerShots[i].speed;
//
//                DrawTexturePro(playerShots[i].texture, sourceShotTextRectangle,
//                    playerShots[i].destRectangle,
//                    { targetWidth / 2.f, targetHeight / 2.f },
//                    0, playerShots[i].tint);
//                DrawRectangleLines(playerShots[i].boundingRectangle.x,
//                    playerShots[i].boundingRectangle.y,
//                    playerShots[i].boundingRectangle.width, playerShots[i].boundingRectangle.height, YELLOW);
//                DrawRectangleLines(playerShots[i].destRectangle.x,
//                    playerShots[i].destRectangle.y,
//                    playerShots[i].destRectangle.width, playerShots[i].destRectangle.height, GREEN);
//
//                if (playerShots[i].boundingRectangle.x > screenWidth + playerShots[i].texture.width / 2 ||
//                    playerShots[i].boundingRectangle.x <-playerShots[i].texture.width / 2 ||
//                    playerShots[i].boundingRectangle.y > screenHeight + playerShots[i].texture.height / 2 ||
//                    playerShots[i].boundingRectangle.y < -playerShots[i].texture.height / 2)
//                {
//                    playerShots[i].fired = false;
//                }
//            }
//        }
//
//        for (size_t i = 0; i < nbColors; i++)
//        {
//            checkCollision(playerShots, coloredEnemies[i]);
//        }
//        int colorsDestroyed = 1;
//        
//   
//   
//   
//
//   
//



//
//
//Quadrant getQuadrant(float orientation)
//{
//    if (orientation >= 0 && orientation < 90)
//        return Quadrant::SE;
//    else if (orientation >= 90 && orientation < 180)
//        return Quadrant::SW;
//    else if (orientation >= 180 && orientation < 270)
//        return Quadrant::NW;
//    else
//        return Quadrant::NE;
//
//    return Quadrant::NE;
//}
//

//
//
//void checkCollision(Shot* munitions, Enemy* enemies)
//{
//    for (size_t i = 0; i < nbShots; i++)
//    {
//        if (munitions[i].fired)
//        {
//            for (size_t j = 0; j < nbEnemies; j++)
//            {
//                if (enemies != nullptr) {
//                    Enemy& currentEnemy = *(enemies + j);
//                    if (!currentEnemy.destroyed)
//                    {
//                        if (CheckCollisionRecs(munitions[i].boundingRectangle, currentEnemy.boundingRectangle) &&
//                            ColorToInt(currentEnemy.tint) == ColorToInt(munitions[i].tint))
//                        {
//                            munitions[i].fired = false;
//                            currentEnemy.destroyed = true;
//                        }
//                    }
//                }
//            }
//        }
//    }

