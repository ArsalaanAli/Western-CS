/*
Author: Arsalaan Ali
Description: Class for functionality and logic of minesweeper
Date: Feb 6, 2024
*/
#include <gamelogic.h>
#include <gameui.h>

/*
Name: GameLogic

Description:
Handles the functionality and logic of the minesweeper game.

Parameters: uiInstance - Pointer to the GameUI object to communicate with the user interface

Returns: Initialized GameLogic object
*/
GameLogic::GameLogic(GameUI* uiInstance)
    : gameUI(uiInstance), flags(gameUI->HEIGHT, std::vector<bool>(gameUI->WIDTH, false)), mines(gameUI->HEIGHT, std::vector<bool>(gameUI->WIDTH, false)), adjacentMineCount(gameUI->HEIGHT, std::vector<int>(gameUI->WIDTH, 0)){
    gameInitialized = false;
    clearedSquares = 0; // amount of square cleared by the player, used to check if the player has won
}

/*
Name: checkMines

Description:
Handles the logic for handling a button click in the minesweeper grid.

Parameters:
y - y coordinate of the square clicked
x - x coordinate of the square clicked

Returns: nothing (void)
*/
void GameLogic::checkMines(int y, int x){
    //if this click is this first one, we set the mines so the first button isnt a mine
    if(!gameInitialized){
        setupGameState(y, x);
        gameInitialized = true;
    }
    //if clicked on a flag, we do nothing
    if(flags[y][x]){
        return;
    }
    //if click on a mine, we end the game
    if(mines[y][x]){
        gameUI->setMine(y, x);
        gameUI->gameOver();
        return;
    }
    //if clicked on an empty square with no adjacent tiles, we recusively clear out all adjacent tiles
    if(adjacentMineCount[y][x] == 0){
        emptyTile(y, x);
        return;
    }
    //if clicked on an empty tile, we do nothing
    if(adjacentMineCount[y][x] == EMPTYTILE){
        return;
    }
    //if clicked on a number tile, we set the number of the tile and disable the tile from being clicked again
    gameUI->setNumberTile(y, x, adjacentMineCount[y][x]);
    adjacentMineCount[y][x] = EMPTYTILE;
    clearedSquares++;
    return;
}

/*
Name: checkGameWin

Description:
Checks if the player has won the game.

Returns: nothing (void)
*/
void GameLogic::checkGameWin(){
    int clearSquares = gameUI->HEIGHT * gameUI->WIDTH - NUMMINES;
    if(clearedSquares == clearSquares){
        gameUI->gameWin();
    }
}

/*
Name: flagTile

Description:
Flags or unflags a tile when right-clicked.

Parameters:
y - y coordinate of the square clicked
x - x coordinate of the square clicked

Returns: nothing (void)
*/
void GameLogic::flagTile(int y, int x){
    if(adjacentMineCount[y][x] == EMPTYTILE){
        return;
    }
    flags[y][x] = !flags[y][x];
    gameUI->setFlagTile(y, x, flags[y][x]);
}

/*
Name: emptyTile

Description:
Clears an empty tile and its adjacent tiles recursively.

Parameters:
y - y coordinate of the square clicked
x - x coordinate of the square clicked

Returns: nothing (void)
*/
void GameLogic::emptyTile(int y, int x){
    //if this isnt an empty tile, we return
    if(adjacentMineCount[y][x] != 0){
        return;
    }
    //set this tile to empty in the ui
    gameUI->setEmptyTile(y, x);
    adjacentMineCount[y][x] = EMPTYTILE;
    //increment the count of squares that have been cleared
    clearedSquares++;
    //loop through adjacent tiles and call emptyTile on them if theyre empty
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if((i == 0 && j == 0) || y+i < 0 || y+i >= gameUI->HEIGHT || x+j < 0 || x+j >= gameUI->WIDTH){
                continue;
            }
            if(adjacentMineCount[y+i][x+j] == 0){
                emptyTile(y+i, x+j);
            }
            //if theyre not empty, we set them to a number tile
            else if(adjacentMineCount[y+i][x+j] > 0){
                gameUI->setNumberTile(y+i, x+j, adjacentMineCount[y+i][x+j]);
                adjacentMineCount[y+i][x+j] = EMPTYTILE;
                clearedSquares++;
            }
        }
    }
}



/*
Name: setupGameState

Description:
Initializes the game state by setting up mines and adjacent mine count.

Parameters:
y - y coordinate of the first square clicked
x - x coordinate of the first square clicked

Returns: nothing (void)
*/
void GameLogic::setupGameState(int y, int x){
    setupMines(y, x);
    setupAdjacentMineCount();
}

/*
Name: setupMines

Description:
Randomly places mines on the game board.

Parameters:
y - y coordinate of the first square clicked
x - x coordinate of the first square clicked

Returns: nothing (void)
*/
void GameLogic::setupMines(int y, int x){
    for(int  i = 0; i < NUMMINES; i++){
        int mineX = x;
        int mineY = y;
        //sets random mines in positions that arent the same as the first button clicked
        while((mineX == x && mineY == y) || mines[mineY][mineX]){
            mineX = rand() % gameUI->WIDTH;
            mineY = rand() % gameUI->HEIGHT;
        }
        mines[mineY][mineX] = true;
    }
}

/*
Name: setupAdjacentMineCount

Description:
Calculates the number of adjacent mines for each tile.

Returns: nothing (void)
*/
void GameLogic::setupAdjacentMineCount(){
    for(int y = 0; y < gameUI->HEIGHT; y++){
        for(int x = 0; x < gameUI->WIDTH; x++){
            int mineCount = 0;
            for(int i = -1; i < 2; i++){
                for(int j = -1; j < 2; j++){
                    if((i == 0 && j == 0) || y+i < 0 || y+i >= gameUI->HEIGHT || x+j < 0 || x+j >= gameUI->WIDTH){
                        continue;
                    }
                    if(mines[y+i][x+j]){
                        mineCount++;
                    }
                }
            }
            adjacentMineCount[y][x] = mineCount;
        }
    }
}
