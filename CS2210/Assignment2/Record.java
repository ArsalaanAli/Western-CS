public class Record {
    private String key;
    private int score, level;

    public Record(String key, int score, int level) {
        this.key = key;
        this.score = score;
        this.level = level;
    }

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