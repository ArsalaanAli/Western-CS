public class Node {//node class for graph
    private int id;
    private boolean mark;//private field variables to hold the id of the node and whether it is marked as visited

    public Node(int id) {//constructor
        this.id = id;
        mark = false;//set id of the node and mark as false
    }
    
    public void markNode(boolean mark) {
        this.mark = mark;
    }

    public boolean getMark() {//setter and getter for mark
        return mark;
    }

    public int getId() {//getter for id
        return id;
    }
}