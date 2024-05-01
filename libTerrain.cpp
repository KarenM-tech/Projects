#include "libTerrain.h"
#include <iostream>
#include <sstream>
#include <cassert>
namespace TerrainSpace{
    void Pause()
    {
        cin.ignore(100,'\n');
        cout << "Please retry: " << endl;
        cin.get();
    }
    //function converts a string to an integer
    int convertToInteger(string strNum)
    {
        stringstream ss {strNum};
        int intNum;
        ss >> intNum;
        if(ss.fail()){
            cerr << "Could not convert " << strNum << " to integer."<< endl;
            exit(ERROR_CONV);
        }
        return intNum;
    }
    //function generates a random integer value
    int getRand(int intMin, int intMax)
    {
        assert(intMax>intMin);
        return rand()% (intMax - intMin + 1) + intMin;

    }
    //The allocate memory function allocates memory for the 2d array and also populates the world with EMPTY characters
    twoDArray allocMemory(int intRows, int intCols)
    {
        twoDArray arrGame = new oneDArray[intRows];
        for(int r=0; r< intRows; r++){
            arrGame[r] = new int[intCols];
            for(int c = 0; c< intCols; c++){
                arrGame[r][c] = EMPTY;
            }
        }
        return arrGame;
    }
    //this function places items into the gameworld
    void placeItem(GameWorld& strWorld, int intCount, int intItem){
        for(int n=0; n< intCount; n++)
        {
            int intRow; //= getRand(0,strWorld.intRows-1);
            int intCol; //= getRand(0,strWorld.intCols -1);
            while(strWorld.arrGame[intRow][intCol]!=EMPTY)
            {
                intRow = getRand(0,strWorld.intRows-1);
                intCol = getRand(0,strWorld.intCols-1);
            }
            strWorld.arrGame[intRow][intCol] = intItem;
        }

    }
    //initailise Game with items. in this order Obstacles, Mines, Temporary energy units
    GameWorld initialiseWorld(int intRows, int intCols, int intObstacles, int intMines, int intTempEnergy){
        GameWorld strWorld;
        strWorld.intRows = intRows;
        strWorld.intCols = intCols;
        strWorld.arrGame = allocMemory(intRows, intCols);
        //initialise player
        strWorld.intPlayerRow = intRows-1;
        strWorld.intPlayerCol = getRand(0,intCols-1);
        strWorld.intPlayerEnergy = INITIAL_ENERGY;
        //initialise the state of the game
        strWorld.state = RUNNING;
        //place items into the gameworld 2d array
        placeItem(strWorld, intObstacles,OBSTACLE);
        placeItem(strWorld, intMines, MINE);
        placeItem(strWorld, intTempEnergy, ENERGY_UNIT);

        return strWorld;
    }
    //This function displays the 2D game world onto the console
    void printWorld(GameWorld stcWorld)
    {
        system("cls");
        for(int r = 0; r< stcWorld.intRows; r++)
        {
            for(int c=0; c < stcWorld.intCols; c++)
            {
                if(stcWorld.intPlayerRow == r && stcWorld.intPlayerCol == c)
                    cout << PLAYER << " ";
                else
                    cout << FEATURES[stcWorld.arrGame[r][c]] << " ";
            }

            cout << endl;
        }
        cout << "How to play:"<< endl
            << "w: MOVE UP "<< endl
            << "S: MOVE DOWN " << endl
            << "A: LEFT" << endl
            << "D: RIGHT" << endl
            << "?: For instructions" << endl;
            cout << "PLAYER ENERGY: " << stcWorld.intPlayerEnergy << endl;
    }
    //function checks if the destination location(cell) is in the gameworld
    bool isInWorld(int intRows, int intCols, int intRow, int intCol)
    {
        bool isIT = (intRow>=0 && intRow < intRows &&
               intCol>=0 && intCol < intCols);
        if(isIT){
            return true;
        }else{
            //Pause();
            cout << "YOU CANT MOVE OUTSIDE GAME WORLD"<< endl;
            Pause();
            return false;
        }
    }
    //function deals with whether the player has won the game. The player does not actually occupy the last row
    bool hasWonGame(GameWorld& stcGame,int intRow)
    {
        if(intRow == 0){
            stcGame.state = WON;
            cout << "YOU HAVE REACHED THE FINISH LINE!!" << endl;
            cout << "YOU HAVE WON!!!"<<endl ;

        }
        return true;
    }
    //if the destination contains a mine- the player has lost.
    //player cannot occupy the same space as an obstacle
    //This function deals with player movement
    void movePlayer(GameWorld& strWorld, char chInput)
    {
        int intPRow = strWorld.intPlayerRow;
        int intPCol = strWorld.intPlayerCol;
        switch(chInput)
        {
            case 'w':
                intPRow--;
                break;
            case 's':
                intPRow++;
                break;
            case 'd':
                intPCol++;
                break;
            case 'a':
                intPCol--;
                break;
        }


        //check if new location is empty
        if(strWorld.arrGame[intPRow][intPCol]==EMPTY)
        {
            //empty old location
            strWorld.arrGame[strWorld.intPlayerRow][strWorld.intPlayerCol] = EMPTY;
            //place player in new space/location
            strWorld.arrGame[intPRow][intPCol] = PLAYER;
            //Update variables
            strWorld.intPlayerRow = intPRow;
            strWorld.intPlayerCol = intPCol;
            //-1 energy with each movement
            strWorld.intPlayerEnergy -=1;

        }//if player moves over temporary energy
        else if (strWorld.arrGame[intPRow][intPCol]==ENERGY_UNIT)
        {
            strWorld.arrGame[intPRow][intPCol] = EMPTY;
            strWorld.arrGame[intPRow][intPCol] = PLAYER;
            strWorld.intPlayerRow = intPRow;
            strWorld.intPlayerCol = intPCol;
            //+5 energy when the player moves over a Temporary energy unit
            strWorld.intPlayerEnergy+=5;
           strWorld.arrGame[intPRow][intPCol] = EMPTY;
        }//if the player moves over a mine- they lose the game
        else if (strWorld.arrGame[intPRow][intPCol]==MINE)
        {
            cout << "YOU HAVE BUMPED INTO A MINE. YOU HAVE LOST THE GAME :(" << endl;
            strWorld.state = LOST;
        }
        // if the player runs out of energy- they lose the game
        if(strWorld.intPlayerEnergy == 0)
        {
            cout << "ENERGY LEVEL 0. YOU HAVE LOST THE GAME :(" << endl;
            strWorld.state = LOST;
        }
        //if the player reaches the top row of the gameworld- they win the game
        hasWonGame(strWorld, intPRow);
    }

    //function deallocates memory to prevent memory leaks
    void deallocMemory(twoDArray& arrGame, int intRows){
        assert(arrGame != nullptr);
        for(int r= 0; r< intRows; r++)
            delete[] arrGame[r];
        delete[] arrGame;
        arrGame = nullptr;
    }


}
