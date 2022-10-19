public class Evaluate {
    //instance variables
    private char[][] gameBoard;//holds the state of the game board
    private int tilesToWin;//signifies the number of tiles needed to win

    public Evaluate(int size, int tilesToWin, int maxLevel) {//constructor
        this.tilesToWin = tilesToWin;//initialize tilesToWin
        gameBoard = new char[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                gameBoard[i][j] = 'e';//initilizes every index of gameboard to the empty character
            }
        }
    }

    public Dictionary createDictionary() {//returns a dictionary object with the size of 9901(prime number)
        return new Dictionary(9901);
    }

    public Record repeatedState(Dictionary dict) {
        String gameState = this.getGameState();
        return dict.get(gameState);//checks if the game state exists in the dictionary and returns the corresponding record if it does, otherwise returns null
    }
    
    public void insertState(Dictionary dict, int score, int level) {
        String gameState = this.getGameState();
        Record curRecord = new Record(gameState, score, level);//creates a record for the given parameters and the current gameState
        dict.put(curRecord);//adds the created record to the dictionary
    }

    public void storePlay(int row, int col, char symbol) {
        gameBoard[row][col] = symbol;//updates the given position on the gameboard with the given symbol
    }
    
    public boolean squareIsEmpty(int row, int col) {
        return gameBoard[row][col] == 'e';//checks if the board has the character 'e' at the given position
    }

    public boolean tileOfComputer(int row, int col) {
        return gameBoard[row][col] == 'c';//checks if the board has the character 'c' at the given position
    }

    public boolean tileOfHuman(int row, int col) {
        return gameBoard[row][col] == 'h';//checks if the board has the character 'h' at the given position
    }

    public boolean wins(char symbol) {//function checks if the character given is winning in the current gamestate
        for (int i = 0; i < gameBoard.length; i++) {
            for (int j = 0; j < gameBoard.length; j++) {//function loops through every character in the current gamestate
                for (int dir = 0; dir < 4; dir++) {//loops 4 times for the 4 possible directions a player can win (vetical, horizontal, 2 diagonals)
                    for (int count = 0; count < tilesToWin; count++) {//loops the amount of tiles in a row neeed to win
                        if (dir == 0) {//each direction is checked independently
                            if (i + count >= gameBoard.length || gameBoard[i + count][j] != symbol) {
                                break;//if the sequence of characters is broken by the wrong symbol or going out of bounds, the loop is broken
                            }
                            if (count == tilesToWin - 1) {
                                return true;//if the entire loop goes through without being brokem, the function returns true, because this player has enough tiles in a row to win
                            }
                        }
                        if (dir == 1) {//same thing as above, but for a different direction
                            if (j + count >= gameBoard.length || gameBoard[i][j + count] != symbol) {
                                break;
                            }
                            if (count == tilesToWin - 1) {
                                return true;
                            }
                        }
                        if (dir == 2) {//same thing as above, but for a different direction
                            if (i + count >= gameBoard.length || j + count >= gameBoard.length
                                    || gameBoard[i + count][j + count] != symbol) {
                                break;
                            }
                            if (count == tilesToWin - 1) {
                                return true;
                            }
                        }
                        if (dir == 3) {//same thing as above, but for a different direction
                            if (i + count >= gameBoard.length || j - count < 0
                                    || gameBoard[i + count][j - count] != symbol) {
                                break;
                            }
                            if (count == tilesToWin - 1) {
                                return true;
                            }
                        }

                    }
                }
            }
        }
        return false;//if no win condition is found in the entire game board, then false is returned
    }

    public boolean isDraw() {//checks to see if its possible to play any moves in the current game board
        for (int i = 0; i < gameBoard.length; i++) {
            for (int j = 0; j < gameBoard.length; j++) {//loops through the current game board
                if (gameBoard[j][i] == 'e') {//checks to see if there are any empty tiles left in the game board
                    return false;//if there are any empty tiles left in the game board then false is returned
                }
            }
        }
        return true;//if there are no empty tiles left in the game board, the true is returned because the game is a draw
    }

    public int evalBoard() {//function to check what state the current game board is in
        if (this.wins('c')) {
            return 3;//return 3 if computer is winning
        }
        else if (this.isDraw()) {
            return 2;//return 2 if its a draw
        }
        else if (this.wins('h')) {
            return 0;//return 0 if human is winning
        }
        else {
            return 1;//otherwise return 1 if none of the above states are true
        }
    }


    private String getGameState() {//function to return the current game state represented as a string
        String gameState = "";//initialize a string to hold the representation of the current game state
        for (int i = 0; i < gameBoard.length; i++) {
            for (int j = 0; j < gameBoard.length; j++) {//loop through the game board
                gameState += gameBoard[j][i];//add the characters in the game board to the string
            }
        }
        return gameState;//return the string
    }

}
