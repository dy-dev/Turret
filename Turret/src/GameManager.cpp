#include "raylib.h"
#include "Enemy.h"
#include "Player.h"
#include "Utilities.h"
#include "GameManager.h"
#include <stdio.h>



GameManager::GameManager()
    : m_Player{ nullptr }
    , m_bGameOver{ false }
    , m_BackgroundColor{ WHITE }
    , m_EnemiesArray{ nullptr }
    , m_iNbEnemybyColorArray{ 0 }
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


void GameManager::initEnemies()
{
    m_EnemiesArray = new Enemy * [NB_COLORS];

    for (size_t i = 0; i < NB_COLORS; i++)
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

void GameManager::runGame()
{
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        int nbColorDestroyed = 0;
        BeginDrawing();
        ClearBackground(m_BackgroundColor);

        if (!m_bGameOver)
        {
            m_bGameOver = manageEnemies(nbColorDestroyed);

            Vector2 playerDirection = m_Player->update(m_EnemiesArray, m_iNbEnemybyColorArray);

            manageButtonClick(playerDirection);
            m_Player->draw();

            drawVisualAids();
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


void GameManager::drawVisualAids()
{
    //DrawText(colorstream.str().c_str(), 190, 250, 20, LIGHTGRAY);
    DrawLine(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, GetMousePosition().x, GetMousePosition().y, GREEN);
    DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, GREEN);
    DrawLine(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, GREEN);
}


void GameManager::manageButtonClick(Vector2 p_PlayerDirection)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        bool isEnemyClicked = checkClickOnEnemy();
        if (!isEnemyClicked) {
            m_Player->shoot(p_PlayerDirection);
        }
    }
    int colorsDestroyed = 1;
}

bool GameManager::checkClickOnEnemy()
{
    //Check if an enemy is clicked
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (m_EnemiesArray[i] == nullptr)
            continue;

        int j = -1;
        while (++j < m_iNbEnemybyColorArray[i])
        {
            if (m_EnemiesArray[i][j].getDestroyed())
                continue;

            if (CheckCollisionPointRec(GetMousePosition(), m_EnemiesArray[i][j].getBoundingRectangle()))
            {
                unsigned long long adress = (unsigned long long) & (m_EnemiesArray[i][j]);
                char buf[24];
                sprintf_s(buf, "%llX", adress);
                changeTint(buf);
                return true;
            }
        }
    }
    return false;
}

bool GameManager::manageEnemies(int& nbColorDestroyed)
{
    for (int i = 0; i < NB_COLORS; i++) {
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
                    break;
                }
                continue;
            }
            m_EnemiesArray[i][j].update();
            m_EnemiesArray[i][j].draw();
        }
    }

    return nbColorDestroyed == NB_COLORS;
}










