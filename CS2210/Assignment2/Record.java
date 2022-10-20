class Record {//record class, holds information about the state of the board
    //instance variables
    private String key;//string to hold gamestate
    private int score, level;//holds the score and level of the gamestate

    public Record(String key, int score, int level) {//constructor sets the value of the instance variables to the parameters
        this.key = key;
        this.score = score;
        this.level = level;
    }

    //getter functions for instance variables
    public String getKey() {
        return this.key;
    }

    public int getScore() {
        return this.score;
    }

    public int getLevel() {
        return this.level;
    }    
}