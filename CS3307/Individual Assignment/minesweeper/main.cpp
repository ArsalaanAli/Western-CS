/*
Author: Arsalaan Ali
Description: Main class, runs the program and opens window
Date: Feb 6, 2024
*/
#include "gameui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GameUI gameWindow;
    gameWindow.showMaximized();
    return app.exec();
}
