public class BinarySearchTree implements BinarySearchTreeADT{

    private BNode root;

    public BinarySearchTree() {
        this.root = new BNode();
    }

    public BNode getRoot() {
        return this.root;
    }

    public Pel get(BNode r, Location key) {
        if (r == null) {
            return null;
        }

        Location curLoc = r.getData().getLocation();
        if (key.compareTo(curLoc) == 0) {
            return r;
        }
        if (r.isLeaf()) {
            return null;
        }
        if (key.compareTo(curLoc) == -1) {
            return get(r.leftChild(), key);
        }
        if (key.compareTo(curLoc) == 1) {
            return get(r.rightChild(), key);
        }
    }

    public void put(BNode r, Pel data) throws DuplicatedKeyException {
        Location curLoc = r.getData().getLocation();
        Location dataLoc = data.getLocation();

        if (curLoc.compareTo(data.getLocation()) == 0) {
            throw new DuplicatedKeyException("Key already exists in the BST");
        }
        if (dataLoc.compareTo(curLoc) == -1) {
            if (r.leftChild() == null) {
                r.setLeftChild()
            }
        }
    }
}
