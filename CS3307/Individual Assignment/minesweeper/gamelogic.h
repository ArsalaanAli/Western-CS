/*
Author: Arsalaan Ali
Description:
Date: Feb 6, 2024
*/
#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QMainWindow>
#include <QWidget>

class GameUI;

class GameLogic {
public:
    GameLogic(GameUI* uiInstance);
    const int NUMMINES = 10;
    void checkMines(int y, int x);
    void checkGameWin();
    void flagTile(int y, int x);

private:
    GameUI *gameUI;
    std::vector<std::vector<bool>> flags;
    std::vector<std::vector<bool>> mines;
    std::vector<std::vector<int>> adjacentMineCount;
    const int EMPTYTILE = -1;
    const int FLAGTILE = -2;
    int clearedSquares;
    bool gameInitialized;
    void emptyTile(int y, int x);
    void setupGameState(int y, int x);
    void setupMines(int y, int x);
    void setupAdjacentMineCount();
};



#endif // GAMELOGIC_H
