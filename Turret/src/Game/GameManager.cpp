#include <stdio.h>

#include "raylib.h"

#include "Enemies/Enemy.h"
#include "Player/Player.h"
#include "Game/Utilities.h"
#include "Game/GameManager.h"
#include "Game/Spawner.h"


GameManager* GameManager::s_GameManager = nullptr;

GameManager::GameManager()
    : m_Player{ nullptr }
    , m_bGameOver{ false }
    , m_BackgroundColor{ WHITE }
    , m_EnemiesArray{ nullptr }
    , m_iNbEnemybyColorArray{ new int[GameManager::NB_COLORS] }
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
    m_Player = new Player{ Vector2{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, SCREEN_WIDTH, SCREEN_HEIGHT, "./assets/textures/Player.png" };

    /**
    * Enemies initialisation
    */
    m_Spawner = new Spawner();
    m_EnemiesArray = new GraphicObjects * *[GameManager::NB_COLORS];

    m_Spawner->CreateEnemies(0, m_EnemiesArray, m_iNbEnemybyColorArray);
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

            m_Player->update();

            manageButtonClick();
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


GameManager& GameManager::getInstance()
{
    if (s_GameManager == nullptr) {
        s_GameManager = new GameManager();
    }
    return *s_GameManager;
}


void GameManager::drawVisualAids()
{
    //DrawText(colorstream.str().c_str(), 190, 250, 20, LIGHTGRAY);
    DrawLine(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, GetMousePosition().x, GetMousePosition().y, GREEN);
    DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, GREEN);
    DrawLine(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, GREEN);
}


void GameManager::manageButtonClick()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        bool isEnemyClicked = checkClickOnEnemy();
        if (!isEnemyClicked) {
            m_Player->onClick();
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
            /*if (((Destroyable&)m_EnemiesArray[i][j]).getDestroyed())
                continue;

            if (CheckCollisionPointRec(GetMousePosition(), m_EnemiesArray[i][j].getBoundingRectangle()))
            {
                unsigned long long adress = (unsigned long long) & (m_EnemiesArray[i][j]);
                char buf[24];
                sprintf_s(buf, "%llX", adress);
                changeTint(buf);
                return true;
            }   */
        }
    }
    return false;
}

bool GameManager::manageEnemies(int& nbColorDestroyed)
{
    for (int i = 0; i < NB_COLORS; i++) {
        int j = -1;
        int nbDestroyed = 0;
        if (m_EnemiesArray[i] == nullptr) {
            nbColorDestroyed++;
            continue;
        }


        while (++j < m_iNbEnemybyColorArray[i]) {
            if (m_EnemiesArray[i][j] != nullptr) {
                Destroyable* dest = dynamic_cast<Destroyable*>( m_EnemiesArray[i][j]);
                bool destroyed = dest->getDestroyed();
                if (destroyed)
                {
                    nbDestroyed++;
                    if (nbDestroyed == m_iNbEnemybyColorArray[i]) {
                        for (size_t k = 0; k < nbDestroyed; k++)
                        {
                            delete m_EnemiesArray[i][k];
                        }
                        delete[] m_EnemiesArray[i];
                        m_EnemiesArray[i] = nullptr;
                        break;
                    }
                    continue;
                }
                m_EnemiesArray[i][j]->update();
                m_EnemiesArray[i][j]->draw();
            }
        }
    }

    return nbColorDestroyed == NB_COLORS;
}










