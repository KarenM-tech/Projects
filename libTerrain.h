#ifndef LIBTERRAIN_H_INCLUDED
#define LIBTERRAIN_H_INCLUDED

#include <iostream>
using namespace std;
namespace TerrainSpace{
    //enumeration for the Game state
    enum eState{
        RUNNING,
        WON,
        LOST,
        QUIT
    };
    //enumeration for the Game Features
    enum eFeatures{
        EMPTY,
        OBSTACLE,
        MINE,
        ENERGY_UNIT
    };

    //declare constants
    const int ERROR_CONV = -1;
    const int ERROR_ARGC = -2;
    //declare character array of game features
    const char FEATURES[] = {' ', '#', 'M', 'T'};

    const char PLAYER = 'P';
    const int INITIAL_ENERGY = 7;
    //create aliases
    typedef int** twoDArray;
    typedef int* oneDArray;
    //declare game world record structure
    struct GameWorld{
        twoDArray arrGame;
        int intRows;
        int intCols;
        int intPlayerRow;
        int intPlayerCol;
        int intPlayerEnergy;
        eState state;
    };

    //Declare functions
    void Pause();
    int convertToInteger(string strNum);
    twoDArray allocMemory(int intRows, int intCols);
    int getRand(int intMin, int intMax);
    void placeItem(GameWorld& strucGame, int intCount, int intItem);
    GameWorld initialiseWorld(int intRows, int intCols, int intObstacles, int intMines, int intTempEnergy);
    void printWorld(GameWorld stcWorld);
    bool isInWorld(int intRows, int intCols, int intRow, int intCol);
    void movePlayer(GameWorld& strWorld, char chInput);
    bool hasWonGame(GameWorld& stcGame,int intRow);
    void deallocMemory(twoDArray& arrGame, int intRows);

}


#endif // LIBTERRAIN_H_INCLUDED
