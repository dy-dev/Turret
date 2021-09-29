#include <iostream>
#include "Utils.h"

float selectEnemySpeed() 
{
    std::cout << "Select your enemies' speed : " << std::endl;
    float speed;
    std::cin >> speed;

    return speed;
}
