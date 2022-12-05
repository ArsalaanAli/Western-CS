public class MyObject implements MyObjectADT {
    private int id, width, height;//private field variables

    private String type;

    private Location pos;

    private BinarySearchTree tree;

    public MyObject(int id, int width, int height, String type, Location pos) {//initializes the object with the given values
        this.id = id;
        this.width = width;
        this.height = height;
        this.type = type;
        this.pos = pos;
        this.tree = new BinarySearchTree();
    }

    //GETTER AND SETTER FUNCTIONS
    public void setType(String type) {
        this.type = type;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }
    
    public String getType() {
        return type;
    }

    public int getId() {
        return id;
    }

    public Location getLocus() {
        return pos;
    }

    public void setLocus(Location value) {
        this.pos = value;
    }

    public void addPel(Pel pix) throws DuplicatedKeyException {
        tree.put(tree.getRoot(), pix);//addes given pel to tree
    }

    public boolean intersects(MyObject otherObject) {//checks if two objects intersect

        boolean rect = rectInt(otherObject);//check if the rectangles intercept
        if (!rect) {
            return false;//if they dont return false
        }
        Pel curPel;//pel holding the smallest pel in tree
        try{
            curPel = tree.smallest(tree.getRoot());//use try and catch to set value becuase of possible exception
        }
        catch (Exception e) {
            return false;
        }
        while (curPel != null) {//loop through all the pels in the tree
            int calcx = this.pos.getx() + curPel.getLocus().getx() - otherObject.getLocus().getx();
            int calcy = this.pos.gety() + curPel.getLocus().gety() - otherObject.getLocus().gety();
            Location checkPel = new Location(calcx, calcy);
            if (otherObject.containsPel(checkPel)) {//check if the pel matches any pel in the other tree
                return true;
            }
            curPel = tree.successor(tree.getRoot(), curPel.getLocus());//if no match found, go to the next biggest pel in tree
        }
        return false;//if no match found return false

    }
    
    boolean containsPel(Location loc) {//check if a pel is in the tree of this object
        return (tree.get(tree.getRoot(), loc) != null);
    }

    private boolean rectInt(MyObject other) {//calculate if this rectangle overlaps the other rectangle

        int curx = this.pos.getx();
        int curx2 = curx + this.width;
        int cury = this.pos.gety();
        int cury2 = cury + this.height;
        int otherx = other.pos.getx();
        int otherx2 = otherx + other.getWidth();
        int othery = other.pos.gety();
        int othery2 = othery + other.getHeight();

        boolean xintercept = ((otherx > curx && otherx <= curx2) || (otherx2 > curx && otherx2 < curx2));
        boolean yintercept = ((othery > cury && othery <= cury2) || (othery2 > cury && othery2 < cury2));

        return (xintercept && yintercept);//if the two rectanlges are intersecting return true
    }


}
