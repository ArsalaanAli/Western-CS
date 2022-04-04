public class TreeBuilder<T> {
    public LinkedBinaryTree<T> buildTree(T[] data) {//Method that returns a linked binary tree in level traversal order based on a set of data

        LinkedQueue<T> dataQueue = new LinkedQueue<T>();//a queue that holds all the different data values for the nodes in the tree

        LinkedQueue<BinaryTreeNode<T>> parentQueue = new LinkedQueue<BinaryTreeNode<T>>();//a queue used to determine which node will be the next parent node when building the tree

        for (T cur : data) {
            dataQueue.enqueue(cur);//adding all of the data values to the data queue
        }

        LinkedBinaryTree<T> tree = new LinkedBinaryTree<T>(dataQueue.dequeue());//the linked binary tree that will be returned at the end of the function
        parentQueue.enqueue(tree.getRoot());//adding the first node in the tree to the parent queue, so that the next elements will be added as children to this node

        while (!dataQueue.isEmpty()) {//looping through all of the data values

            T a = dataQueue.dequeue();
            T b = dataQueue.dequeue();//getting the firs two elements from the data queue

            BinaryTreeNode<T> parent = parentQueue.dequeue();//getting the parent node from the parent queue, so that the data elemets can be added to this node

            if (a != null) {//if either a or b are null, then nothing needs to be added to the parent node
                parent.setLeft(new BinaryTreeNode<T>(a));
                parentQueue.enqueue(parent.getLeft());//if a isnt null then its added to the left side of the parent node
            }
            if (b != null) {
                parent.setRight(new BinaryTreeNode<T>(b));//if either a or b are null, then nothing needs to be added to the parent node
                parentQueue.enqueue(parent.getRight());//if b isnt null then its added to the right side of the parent node
            }
        }
        return tree;//returning the tree once all of the data values have been added
    }
}
