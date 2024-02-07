#include <gameui.h>

/*
Name: GameUI

Description:
Constructor for GameUI.
Sets up the grid of squares and creates a gamelogic object to handle all of the minesweeper logic.
Initializes the end game dialog for when the game is over.

Parameters: *parent - pointer to the parent of this object

Returns: Initialized GameUI Object
*/
GameUI::GameUI(QWidget *parent)
    : QMainWindow(parent), MINEICON(":/bomb_explode.png"), FLAGICON(":/mine_flag.png")
{
    // Initialize the grid layout
    gridLayout = new QGridLayout;
    // Create the grid of squares
    createGrid(gridLayout);
    // Set up the layout for the screen
    screenSetup(gridLayout);
    // Create a GameLogic object to handle the game logic
    gameLogic = new GameLogic(this);
    // Initialize the end game dialog
    endGameDialog = new QDialog();
    // Set up the dialog
    setupDialog(endGameDialog);
}



/*
Name: setMine

Description:
Sets the UI button in the grid to a mine.

Parameters:
y - y coordinate of the square clicked
x - x coordinate of the square clicked

Returns: nothing (void)
*/
void GameUI::setMine(int y, int x){
    QPushButton *currentButton = (QPushButton*) this->gridLayout->itemAtPosition(y, x)->widget();
    currentButton->setIcon(MINEICON);
}

/*
Name: setNumberTile

Description:
Sets the UI button in the grid to a number tile with the number of mines surrounding it.

Parameters:
y - y coordinate of the square clicked
x - x coordinate of the square clicked
num - number of mines surrounding this square

Returns: nothing (void)
*/
void GameUI::setNumberTile(int y, int x, int num){
    QPushButton *currentButton = (QPushButton*) this->gridLayout->itemAtPosition(y, x)->widget();
    currentButton->setText(QString::number(num));
    setEmptyTile(y, x);
}

/*
Name: setEmptyTile

Description:
Sets the UI button in the grid to an empty tile, meaning it has been cleared.

Parameters:
y - y coordinate of the square clicked
x - x coordinate of the square clicked

Returns: nothing (void)
*/
void GameUI::setEmptyTile(int y, int x){
    QPushButton *currentButton = (QPushButton*) this->gridLayout->itemAtPosition(y, x)->widget();
    currentButton->setFlat(true);
}

/*
Name: setFlagTile

Description:
Sets the UI button in the grid to a flag, or changes it from a flag back into an empty tile.

Parameters:
y - y coordinate of the square clicked
x - x coordinate of the square clicked
flag - bool for whether to turn square into a flag or an empty icon

Returns: nothing (void)
*/
void GameUI::setFlagTile(int y, int x, bool flag){
    QPushButton *currentButton = (QPushButton*) this->gridLayout->itemAtPosition(y, x)->widget();
    currentButton->setIcon(flag ? FLAGICON : QIcon());
}

/*
Name: triggerFlag

Description:
Triggers flagging of a tile when right-clicked.

Parameters:
y - y coordinate of the square clicked
x - x coordinate of the square clicked

Returns: nothing (void)
*/
void GameUI::triggerFlag(int y, int x){
    gameLogic->flagTile(y, x);
}

/*
Name: gameOver

Description:
Displays a dialog when the game is over.

Returns: nothing (void)
*/
void GameUI::gameOver(){
    showDialog(endGameDialog, "GAME OVER");
}

/*
Name: gameWin

Description:
Displays a dialog when the game is won.

Returns: nothing (void)
*/
void GameUI::gameWin(){
    showDialog(endGameDialog, "YOU WIN");
}

/*
Name: handleButtonClick

Description:
Handles button click for the minesweeper grid.
After every click, handle the logic for clearing that button or detonating a mine.
Check if player has won the game.

Parameters:
y - y coordinate of the square clicked
x - x coordinate of the square clicked

Returns: nothing (void)
*/
void GameUI::handleButtonClick(int y, int x)
{
    // Check for mines and handle game logic
    gameLogic->checkMines(y, x);
    // Check if the player has won the game
    gameLogic->checkGameWin();
}

/*
Name: createGrid

Description:
Creates the grid of buttons for the game UI.

Parameters:
gridLayout - QGridLayout object for the game UI

Returns: nothing (void)
*/
void GameUI::createGrid(QGridLayout *gridLayout){
    for(int y = 0; y<HEIGHT; y++){
        for(int x = 0; x<WIDTH; x++){
            QPushButton *temp = new QPushButton("");
            //create a right click event handler
            RightClickFilter *filter = new RightClickFilter(this, y, x);
            temp->installEventFilter(filter);
            temp->setFixedSize(40, 40);

            // Connect button click to handleButtonClick slot
            connect(temp, &QPushButton::clicked, this, [this, y, x]() {
                handleButtonClick(y, x);
            });
            gridLayout->addWidget(temp, y, x);
        }
    }
}

/*
Name: resetGame

Description:
Resets the game UI for a new game.

Returns: nothing (void)
*/
void GameUI::resetGame(){
    gridLayout = new QGridLayout;
    createGrid(gridLayout);
    screenSetup(gridLayout);
    gameLogic = new GameLogic(this);
}

/*
Name: screenSetup

Description:
Sets up the layout for the game UI screen.

Parameters:
gridLayout - QGridLayout object for the game UI

Returns: nothing (void)
*/
void GameUI::screenSetup(QGridLayout *gridLayout){
    // Create a central widget to contain the grid layout
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(gridLayout);
    gridLayout->setSpacing(1);

    // Get the central area of the GameUI
    QFrame *centralArea = new QFrame(this);
    setCentralWidget(centralArea);

    QVBoxLayout *centralLayout = new QVBoxLayout(centralArea);
    centralLayout->addWidget(centralWidget, 0, Qt::AlignCenter);

    // Set the layout for the central area
    centralArea->setLayout(centralLayout);
}

/*
Name: showDialog

Description:
Displays a dialog with a given title.

Parameters:
endGameDialog - Pointer to the end game dialog
title - Title of the dialog

Returns: nothing (void)
*/
void GameUI::showDialog(QDialog *endGameDialog, std::string title){
    endGameDialog->setWindowTitle(QString::fromStdString(title));
    endGameDialog->exec();
}

/*
Name: setupDialog

Description:
Sets up the end game dialog with retry and exit buttons.

Parameters:
endGameDialog - Pointer to the end game dialog

Returns: nothing (void)
*/
void GameUI::setupDialog(QDialog *endGameDialog){
    QVBoxLayout *layout = new QVBoxLayout(endGameDialog);

    endGameDialog->setMinimumSize(300, 200);

    QPushButton *retryButton = new QPushButton("Retry");
    QPushButton *exitButton = new QPushButton("Exit");

    // Connect retryButton clicked signal to resetGame
    connect(retryButton, &QPushButton::clicked, [this, endGameDialog]() {
        qDebug() << "Retry button clicked";
        resetGame();
        endGameDialog->close();
    });

    // Connect exitButton clicked signal to quit the application
    connect(exitButton, &QPushButton::clicked, []() {
        qDebug() << "Exit button clicked";
        QApplication::quit();
    });

    // Add buttons to the layout
    layout->addWidget(retryButton);
    layout->addWidget(exitButton);

    // Set the layout for the dialog
    endGameDialog->setLayout(layout);
}

/*
Name: RightClickFilter

Description:
Constructor for RightClickFilter class.

Parameters:
parent - Pointer to the parent GameUI object
y - y coordinate of the square clicked
x - x coordinate of the square clicked

Returns: Initialized RightClickFilter Object
*/
RightClickFilter::RightClickFilter(GameUI *parent, int y, int x){
    this->y = y;
    this->x = x;
    this->parent = parent;
}

/*
Name: eventFilter

Description:
Filters the mouse events for right clicks on the grid.

Parameters:
obj - QObject for the filtered event
event - QEvent for the filtered event

Returns: true if the event was handled, otherwise false
*/
bool RightClickFilter::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::RightButton) {
            parent->triggerFlag(y, x);
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}
