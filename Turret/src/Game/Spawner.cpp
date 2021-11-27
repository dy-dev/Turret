#include <raylib.h>
#include "Enemies/FlyingPawn.h"
#include "Game/GameManager.h"
#include "Game/Spawner.h"
#include <Game/Utilities.h>

Spawner::Spawner()
{
}

void Spawner::ReadConfig()
{
}

void Spawner::CreateEnemies(int p_iLevel, GraphicObjects*** p_EnemiesArray, int* p_iNbEnemybyColorArray)
{
    for (size_t i = 0; i < GameManager::NB_COLORS; i++)
    {
        p_iNbEnemybyColorArray[i] = GetRandomValue(1, 1);
        p_EnemiesArray[i] = new GraphicObjects*[p_iNbEnemybyColorArray[i]];
        for (size_t j = 0; j < p_iNbEnemybyColorArray[i]; j++)
        {
            p_EnemiesArray[i][j] = new FlyingPawn();
        }
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
        for (size_t j = 0; j < p_iNbEnemybyColorArray[i]; j++)
        {
           (dynamic_cast<FlyingPawn*>(p_EnemiesArray[i][j]))->setTint((int)colorQuadrant);
        }  
    }

}

void Spawner::SpawnRandomBonus(Vector2 p_Position)
{
}

void Spawner::DefineBonusToGenerate()
{
}

