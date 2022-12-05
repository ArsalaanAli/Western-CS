public class BNode {//node class for bst
    private Pel value;//private field variables
    private BNode left;
    private BNode right;
    private BNode parent;
    
    public BNode(Pel value, BNode left, BNode right, BNode parent) {//initialize a node with given values
        this.value = value;
        this.left = left;
        this.right = right;
        this.parent = parent;
    }

    public BNode() {
        this.value = null;//initialize an empty node
        this.left = null;
        this.right = null;
        this.parent = null;
    }


    //GETTERS AND SETTERS, RETURN AND SET VALUES OF FIELD VARIABLES
    public BNode parent() {
        return this.parent;
    }

    public void setParent(BNode parent) {
        this.parent = parent;
    }

    public void setLeftChild(BNode p) {
        this.left = p;
    }

    public void setRightChild(BNode p) {
        this.right = p;
    }

    public void setContent(Pel value) {
        this.value = value;
    }

    public boolean isLeaf() {
        return (this.left == null && this.right == null);
    }

    public Pel getData() {
        return this.value;
    }

    public BNode leftChild() {
        return this.left;
    }

    public BNode rightChild() {
        return this.right;
    }
}