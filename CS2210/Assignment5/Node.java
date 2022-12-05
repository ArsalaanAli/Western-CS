public class Node {
    private int id;
    private boolean mark;

    public Node(int id) {
        this.id = id;
        mark = false;
    }
    
    public void markNode(boolean mark) {
        this.mark = mark;
    }

    public boolean getMark() {
        return mark;
    }

    int getId() {
        return id;
    }
}