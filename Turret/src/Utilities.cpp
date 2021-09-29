#include <iostream>
#include "Utils.h"
#include "Utilities.h"

int howManyEnemies() {
    int nbEnemies;
    std::cout << "How many enemies do you want to fight ?\n";
    std::cin >> nbEnemies;

    std::cout << "You want them to go at " << selectEnemySpeed() << " pixel / sec!!!" << std::endl;

    return nbEnemies;
}


unsigned int getColor() {
    //0xAE122F
    std::cout << "Please enter the color you want to decompose " << std::endl;
    char colorAsCharArray[16];
    std::cin >> colorAsCharArray;
    return myconvert(colorAsCharArray);
}

unsigned int myconvert(char colorArray[]) {
    unsigned int color = strtol(colorArray, NULL, 16);
    return color;
}

unsigned int getRedVal(int color) {
    return (color >> 16);
}
unsigned int getGreenVal(int color) {
    return ((color >> 8) & 0x00FF);
}
unsigned int getBlueVal(int color) {
    return (color & 0x0000FF);
}