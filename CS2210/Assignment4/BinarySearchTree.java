public class BinarySearchTree implements BinarySearchTreeADT{

    private BNode root;

    public BinarySearchTree() {
        this.root = null;
    }

    public BNode getRoot() {
        return this.root;
    }

    public Pel get(BNode r, Location key) {
        BNode ans = getBNode(r, key);
        return (ans == null ? null : ans.getData());
    }

    private BNode getBNode(BNode r, Location key) {
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
            return getBNode(r.leftChild(), key);
        }
        if (key.compareTo(curLoc) == 1) {
            return getBNode(r.rightChild(), key);
        }
    }

    public void put(BNode r, Pel data) throws DuplicatedKeyException {
        Location curLoc = r.getData().getLocation();
        Location dataLoc = data.getLocation();

        if (curLoc.compareTo(data.getLocation()) == 0) {
            throw new DuplicatedKeyException("Key already exists in the BST");
        }
        else if (dataLoc.compareTo(curLoc) == -1) {
            if (r.leftChild() == null) {
                r.setLeftChild(new BNode(data, null, null, r));
            }
            else{
                put(r.leftChild(), data);
            }
        }
        else if (dataLoc.compareTo(curLoc) == 1) {
            if (r.rightChild() == null) {
                r.setRightChild(new BNode(data, null, null, r));
            }
            else{
                put(r.rightChild(), data);
            }
        }
    }

    public void remove(BNode r, Location key) throws InexistentKeyException {
        BNode removeNode = getBNode(r, key);
        if (removeNode == null) {
            throw InexistentKeyException("This key does not exist in the BST");
        }
        if (removeNode.isLeaf()) {
            replaceChild(removeNode, null);
            return;
        }
        if (removeNode.leftChild() != null && removeNode.rightChild() == null) {
            replaceChild(removeNode, removeNode.leftChild());
            return;
        }
        if (removeNode.leftChild() == null && removeNode.rightChild() != null) {
            replaceChild(removeNode, removeNode.rightChild());
            return;
        }
        if (removeNode.leftChild() != null && removeNode.rightChild() != null) {
            BNode successor = successorBNode(r, key);
            remove(r, successor.getData().getLocation());
            removeNode.setContent(successor.getData());
        }
    }

    private void replaceChild(BNode child, BNode replace) {
        BNode parent = child.parent();
        if (parent.leftChild() == child) {
            parent.setLeftChild(replace);
        } else if (parent.rightChild() == child) {
            parent.setRightChild(replace);
        }
    }

    public Pel successor(BNode r, Location key) {
        BNode ans = successorBNode(r, key);
        return (ans == null ? null : ans.getData());
    }

    private BNode successorBNode(BNode r, Location key){
        if (r == null) {
            return null;
        }
        Location curLoc = r.getData().getLocation();

        if (key.compareTo(curLoc) >= 0) {
            return successorBNode(r.rightChild(), key);
        }
        if (key.compareTo(curLoc) == -1) {
            BNode other = successorBNode(r.leftChild(), key);
            if (other == null) {
                return r;
            } else {
                return other;
            }
        }
    }
    
    public Pel predecessor(BNode r, Location key) {
        BNode ans = predecessorBNode(r, key);
        return (ans == null ? null : ans.getData());
    }

    private BNode predecessorBNode(BNode r, Location key) {
        if (r == null) {
            return null;
        }
        Location curLoc = r.getData().getLocation();

        if (key.compareTo(curLoc) <= 0) {
            return predecessorBNode(r.leftChild(), key);
        }
        if (key.compareTo(curLoc) == 1) {
            BNode other = predecessorBNode(r.rightChild(), key);
            if (other == null) {
                return r;
            } else {
                return other;
            }
        }
    }

}
