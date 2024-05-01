#include "libTerrain.h"
#include <iostream>
#include <ctime>

using namespace std;
using namespace TerrainSpace;

/* Player P starts at the bottom of the game world at a random column with energy level 7.
    A move in any direction subtracts 1 from the player's total energy level. The objective of the game is
    to reach the top of the game world without running out of energy or bumping into a mine.
    M represents a mine. The game ends if the player bumps into a mine
    # represents an immovable obstacle. The player cannot move over this.
    T represents a temporary energy unit. The player's energy level is recharged by 5 units when it passes over one of these.
*/

int main(int argc, char *argv[])
{
    //seed the random number generator
    srand(time(0));
    //check number of arguments provided
    //size of environment (rows and cols), energy units, unmovable obstacles, mines are given as command line arguments
    if (argc != 6){
        cerr << "Not enough arguments " << "TotalRows TotalCols TotalObstacles TempEnergyUnits TotalMines" << endl;
        exit(ERROR_ARGC);
    }
    //Process arguments
    int intRows = convertToInteger(argv[1]);
    int intCols = stoi(argv[2]);
    int obstacles = stoi(argv[3]);
    int enegyUnits = stoi(argv[4]);
    int mines = stoi(argv[5]);

    //initialise world
    GameWorld strcWorld = initialiseWorld(intRows,intCols,obstacles,mines,enegyUnits);

    bool blnContinue = true;
    char chInput = '\0';


    do
    {

        printWorld(strcWorld);

        cin >> chInput;
        chInput =tolower(chInput);      //allows user to enter upper or lower case letters
        //handle player movement
        switch(chInput)
        {
        case 'w':
        case 's':
        case 'd':
        case 'a':
            movePlayer(strcWorld, chInput);
            break;
        case '?':
            cout << "DANGEROUS TERRAIN: INSTRUCTIONS"<< endl;
            cout << "Player P starts with energy level 7." << endl
                 << "Moving subtracts 1 from player's total energy level. " << endl
                 << "The objective of the game is to reach the top of the game world without running out of energy or bumping into a mine. " << endl;
            cout << "M represents a mine. The game ends if the player bumps into a mine" << endl;
            cout << "# represents an immovable obstacle. The player cannot move over this." << endl;
            cout << "T represents a temporary energy unit. The player's energy level is recharged by 5 units when it passes over one of these."<< endl;
            cout << "Enter W S D A to move: ";
            Pause();
            break;
        default:
            cerr << "Invalid option, try again: " << endl;
            Pause();
        }
        if(strcWorld.state !=RUNNING)
            blnContinue = false;
    }while(blnContinue);
    //deallocate memory
    deallocMemory(strcWorld.arrGame, strcWorld.intRows);

    return 0;
}
