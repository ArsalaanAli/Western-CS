public class Evaluate {
    private char[][] gameBoard;
    private int tilesToWin;

    public Evaluate(int size, int tilesToWin, int maxLevel) {
        this.tilesToWin = tilesToWin;
        gameBoard = new char[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                this.gameBoard[i][j] = 'e';
            }
        }
    }

    public Dictionary createDictionary() {
        return new Dictionary(1000099);
    }

    public Record repeatedState(Dictionary dict) {
        String gameState = this.getGameState();
        return dict.get(gameState);
    }
    
    public void insertState(Dictionary dict, int score, int level) {
        String gameState = this.getGameState();
        Record curRecord = new Record(gameState, score, level);
        dict.put(curRecord);
    }

    public void storePlay(int row, int col, char symbol) {
        gameBoard[row][col] = symbol;
    }
    
    public boolean squareIsEmpty(int row, int col) {
        return gameBoard[row][col] == 'e';
    }

    public boolean tileOfComputer(int row, int col) {
        return gameBoard[row][col] == 'c';
    }

    public boolean tileOfHuman(int row, int col) {
        return gameBoard[row][col] == 'h';
    }

    public boolean wins(char symbol) {
        for (int i = 0; i < gameBoard.length; i++) {
            for (int j = 0; j < gameBoard.length; j++) {
                for (int dir = 0; dir < 4; dir++) {
                    for (int count = 0; count < tilesToWin; count++) {
                        if (dir == 0) {
                            if (i + count >= gameBoard.length || gameBoard[i + count][j] != symbol) {
                                break;
                            }
                            if (count == tilesToWin - 1) {
                                return true;
                            }
                        }
                        if (dir == 1) {
                            if (j + count >= gameBoard.length || gameBoard[i][j + count] != symbol) {
                                break;
                            }
                            if (count == tilesToWin - 1) {
                                return true;
                            }
                        }
                        if (dir == 2) {
                            if (i + count >= gameBoard.length || j + count >= gameBoard.length
                                    || gameBoard[i + count][j + count] != symbol) {
                                break;
                            }
                            if (count == tilesToWin - 1) {
                                return true;
                            }
                        }
                        if (dir == 3) {
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
        return false;
    }

    public boolean isDraw() {
        for (int i = 0; i < gameBoard.length; i++) {
            for (int j = 0; j < gameBoard.length; j++) {
                if (gameBoard[j][i] == 'e') {
                    return false;
                }
            }
        }
        return true;
    }

    public int evalBoard() {
        if (this.wins('c')) {
            return 3;
        }
        else if (this.isDraw()) {
            return 2;
        }
        else if (this.wins('h')) {
            return 0;
        }
        else {
            return 1;
        }
    }


    private String getGameState() {
        String gameState = "";
        for (int i = 0; i < gameBoard.length; i++) {
            for (int j = 0; j < gameBoard.length; j++) {
                gameState += gameBoard[j][i];
            }
        }
        return gameState;
    }

}
