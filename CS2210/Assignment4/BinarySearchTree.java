public class BinarySearchTree implements BinarySearchTreeADT {//Binary Search Tree Data Structure

    private BNode root;
    
    public BinarySearchTree() {
        this.root = new BNode();//initialize the root node;
    }

    public BNode getRoot() {
        return this.root;//return the root node
    }

    public Pel get(BNode r, Location key) {
        BNode ans = getBNode(r, key);
        return (ans == null ? null : ans.getData());//get the given data from the tree
    }

    private BNode getBNode(BNode r, Location key) {//private helper function, finds the node with the given key and returns it
        if (r.isLeaf()) {//check if at empty node
            return null;//if no node is found null is returned
        }
        Location curLoc = r.getData().getLocus();//


        if (key.compareTo(curLoc) == 0) {//check if we're at the node we're looking for
            return r;
        }

        if (key.compareTo(curLoc) == -1) {//if the target node is smaller we go left
            if (r.leftChild().isLeaf()) {
                return null;
            }
            return getBNode(r.leftChild(), key);
        }
        if (key.compareTo(curLoc) == 1) {//if the target node is bigger we go right
            if (r.rightChild().isLeaf()) {
                return null;
            }
            return getBNode(r.rightChild(), key);
        }
        return null;//if no node is found null is returned
    }

    public void put(BNode r, Pel data) throws DuplicatedKeyException {//put some data inside the tree
        if (r.isLeaf()) {//if the node is empty, we can put the given data inside
            r.setContent(data);
            r.setLeftChild(new BNode());
            r.setRightChild(new BNode());
            return;
        }

        Location curLoc = r.getData().getLocus();
        Location dataLoc = data.getLocus();

        if (curLoc.compareTo(dataLoc) == 0) {//if the data is already in the tree throw exception
            throw new DuplicatedKeyException("Key already exists in the BST");
        }

        else if (dataLoc.compareTo(curLoc) == -1) {
            put(r.leftChild(), data);//if the data is smaller than the current node go left
        }

        else if (dataLoc.compareTo(curLoc) == 1) {
            put(r.rightChild(), data);//if the data is bigger than the current node go right
        }
    }

    public void remove(BNode r, Location key) throws InexistentKeyException {//removes the given node from the tree

        BNode removeNode = getBNode(r, key);//find the node to be removed

        if (removeNode == null) {
            throw new InexistentKeyException("This key does not exist in the BST");//if the node doesnt exsit throw exception
        }

        if (removeNode.leftChild().isLeaf() && removeNode.rightChild().isLeaf()) {//if the node is a leaf then just set it to an empty node
            if (removeNode.parent() == null) {
                removeNode.setContent(null);
                removeNode.setLeftChild(null);
                removeNode.setRightChild(null);
                return;
            }
            replaceChild(removeNode, new BNode());
            return;
        }
        
        if (removeNode.leftChild().isLeaf()) {
            replaceChild(removeNode, removeNode.rightChild());//if the node only has one child then repalce the node with the child
            return;
        }
        if (removeNode.rightChild().isLeaf()) {
            replaceChild(removeNode, removeNode.leftChild());
            return;
        }

        
        
        BNode successor = successorBNode(r, key);//otherwise find the successor and replace the node with the successor

        Pel replaceData = successor.getData();
        remove(r, successor.getData().getLocus());

        removeNode.setContent(replaceData);

    }


    private void replaceChild(BNode child, BNode replace) {//private function to replace the current node with the content of another node
        child.setContent(replace.getData());
        child.setLeftChild(replace.leftChild());
        child.setRightChild(replace.rightChild());
    }

    public Pel successor(BNode r, Location key) {//returns the successor of the given key
        BNode ans = successorBNode(r, key);
        return (ans == null ? null : ans.getData());
    }

    private BNode successorBNode(BNode r, Location key) {//private function to return the successor of the given key
		
        if (r.isLeaf()) {//if the current node is a lead then there is no successor for this subtree
            return null;
        }
        Location curLoc = r.getData().getLocus();


        if (key.compareTo(curLoc) >= 0) {
            return successorBNode(r.rightChild(), key);//if the key is bigger than the current node, go right
        }


        if (key.compareTo(curLoc) == -1) {//if the key is less than the current node go left
            
            BNode other = successorBNode(r.leftChild(), key);
            if (other == null) {
                return r;//if the left subtree doesnt not have a valid successor, return the current node
            } else {
                return other;//if the left subtree has a valid successor return it
            }
        }
        return null;
    }
    
    public Pel predecessor(BNode r, Location key) {// returns the predecessor  of the given key
        BNode ans = predecessorBNode(r, key);
        return (ans == null ? null : ans.getData());
    }

    private BNode predecessorBNode(BNode r, Location key) {//same as successor function but reversed directions
        if (r.isLeaf()) {
            return null;
        }
        Location curLoc = r.getData().getLocus();

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
        return null;
    }

    public Pel smallest(BNode r) throws EmptyTreeException {//finds the smallest node in the tree
        if (r.isLeaf()) {
            throw new EmptyTreeException("Tree is empty");
        }
        while (!r.leftChild().isLeaf()) {//returns the farthest left child in tree
            r = r.leftChild();
        }
        return r.getData();
    }
    public Pel largest(BNode r) throws EmptyTreeException{//finds the largest node in the tree
        if (r.isLeaf()) {
            throw new EmptyTreeException("Tree is empty");
        }
        while (!r.rightChild().isLeaf()) {//returns the farthest right child in tree
            r = r.rightChild();
        }
        return r.getData();
    }
}