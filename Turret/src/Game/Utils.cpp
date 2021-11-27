#include <iostream>
#include "Game/Utils.h"

float selectEnemySpeed() 
{
    std::cout << "Select your enemies' speed : " << std::endl;
    float speed;
    std::cin >> speed;

    return speed;
}


int selectEnemyNumber(const char* color)
{
    std::cout << "How many enemies of color " << color<< " do you want?" << std::endl;
    int nb;
    std::cin >> nb;

    return nb;
}