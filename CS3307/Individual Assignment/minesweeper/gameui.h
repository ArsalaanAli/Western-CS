/*
Author: Arsalaan Ali
Description:
Date: Feb 6, 2024
*/
#ifndef GAMEUI_H
#define GAMEUI_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QFrame>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QDialog>
#include <QLabel>
#include "qapplication.h"
#include <gamelogic.h>


namespace Ui {
class GameUI;
}

class GameUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameUI(QWidget *parent = nullptr);
    const int HEIGHT = 16;
    const int WIDTH = 30;
    void setMine(int y, int x);
    void setNumberTile(int y, int x, int num);
    void setEmptyTile(int y, int x);
    void setFlagTile(int y, int x, bool flag);
    void triggerFlag(int y, int x);
    void gameOver();
    void gameWin();
private slots:
private:
    QIcon MINEICON;
    QIcon FLAGICON;
    GameLogic *gameLogic;
    QPushButton *m_button;
    QGridLayout *gridLayout;
    QDialog *endGameDialog;
    void handleButtonClick(int row, int col);
    void createGrid(QGridLayout *gridLayout);
    void resetGame();
    void screenSetup(QGridLayout *gridLayout);
    void showDialog(QDialog *endGameDialog, std::string title);
    void setupDialog(QDialog *endGameDialog);
};

class RightClickFilter : public QObject {
    Q_OBJECT
private:
    int y;
    int x;
    GameUI *parent;
public:
    explicit RightClickFilter(GameUI *parent, int y , int x);
    bool eventFilter(QObject *obj, QEvent *event) override;

};


#endif // GAMEUI_H
