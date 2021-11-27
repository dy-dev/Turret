#include <iostream>
#include "raylib.h"
#include "Game/Utils.h"
#include "Game/Utilities.h"
#include "Enemies/Enemy.h"
#include "Assets/Munition.h"
#include "Game/GameManager.h"

int howManyEnemies()
{
    int nbEnemies;
    std::cout << "How many enemies do you want to fight ?\n";
    std::cin >> nbEnemies;

    std::cout << "You want them to go at " << selectEnemySpeed() << " pixel / sec!!!" << std::endl;

    return nbEnemies;
}


unsigned int getColor()
{
    //0xAE122F
    std::cout << "Please enter the color you want to decompose " << std::endl;
    char colorAsCharArray[16];
    std::cin >> colorAsCharArray;
    return myconvert(colorAsCharArray);
}

unsigned int myconvert(char colorArray[])
{
    unsigned int color = strtol(colorArray, NULL, 16);
    return color;
}

unsigned char getRedVal(int color)
{
    return (color >> 16);
}
unsigned char getGreenVal(int color)
{
    return ((color >> 8) & 0x00FF);
}
unsigned char getBlueVal(int color)
{
    return (color & 0x0000FF);
}


void changeTint(const char* pointerToEnemy)
{
    char* end;
    unsigned long long enemyAdress = strtoull(pointerToEnemy, &end, 16);
    Enemy* enemy = (Enemy*)enemyAdress;
    enemy->setTint(ColorToInt(BLACK));
}

Rectangle calculateDestinationRectangle(Vector2 pos, Vector2 origin, Texture2D texture, float scaleFactor)
{
    return {
        pos.x + origin.x,
        pos.y + origin.y,
        (float)texture.width * scaleFactor, (float)texture.height * scaleFactor };
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

void checkCollision(Munition* munitions, GraphicObjects** enemies, int nbEnemies)
{
    for (size_t j = 0; j < nbEnemies; j++)
    {
        if (enemies != nullptr) {
            Enemy* currentEnemy = dynamic_cast<Enemy*>(enemies[j]);
            if (currentEnemy != nullptr && !currentEnemy->getDestroyed())
            {
                if (CheckCollisionRecs(munitions->getBoundingRectangle(), currentEnemy->getBoundingRectangle()) &&
                    ColorToInt(currentEnemy->getTint()) == ColorToInt(munitions->getColor()))
                {
                    munitions->reset();
                    currentEnemy->setDestroyed(true);
                    break;
                }
            }  
        }
    }
}

