// Turret.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Utilities.h"
#include "raylib.h"


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

int main(int argc, char** argv)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    int enemies = howManyEnemies();
    unsigned int passedColor = myconvert(argv[1]);
    Color  backgroundColor = {  getRedVal(passedColor),
                                getGreenVal(passedColor),
                                getBlueVal(passedColor),
                                255};
    ///Find If the response is odd or even
    // - First method : using a mask
    int solution1 = enemies & 1;
    //if solution1 == 0 number is even otherwise is odd

    // - Second method : using the shift operator (and a mask)
    int solution2 = enemies ^ ((enemies >> 1) << 1);
    //It drops the least significant bits and we can use
    //the result as a mask to check if this bit was 1 (= odd)
    //or 0 (= even)
    std::stringstream outstream;
    outstream << "You want to fight " << enemies << " enemies !!";
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
        DrawText(outstream.str().c_str(), 190, 200, 20, LIGHTGRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            colorstream.str("");
            int color = getColor();
            colorstream << "Your color decomposes as follow : " << std::endl;
            colorstream << "\t-Red Value : " << getRedVal(color) << std::endl;
            colorstream << "\t-Green Value : " << getGreenVal(color) << std::endl;
            colorstream << "\t-Blue Value : " << getBlueVal(color) << std::endl;
        }
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
//int main()
//{
//    std::cout << "Hello Warrior!\n";
//    
//    std::cout << "You asked for " << howManyEnemies() << " enemies !!!" << std::endl;
//}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
