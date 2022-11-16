public class BNode {
    private Pel value;
    private BNode left = null;
    private BNode right = null;
    private BNode parent = null;
    
    public BNode(Pel value, BNode left, BNode right, BNode parent) {
        this.value = value;
        this.left = left;
        this.right = right;
        this.parent = parent;
    }

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