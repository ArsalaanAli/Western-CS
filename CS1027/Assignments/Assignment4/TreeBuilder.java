public class TreeBuilder<T> {
    public LinkedBinaryTree<T> buildTree(T[] data) {
        LinkedQueue<T> dataQueue = new LinkedQueue<T>();
        LinkedQueue<BinaryTreeNode<T>> parentQueue = new LinkedQueue<BinaryTreeNode<T>>();
        for (T cur : data) {
            dataQueue.enqueue(cur);
        }
        LinkedBinaryTree<T> tree = new LinkedBinaryTree<T>(dataQueue.dequeue());
        parentQueue.enqueue(tree.getRoot());
        while (!dataQueue.isEmpty()) {
            T a = dataQueue.dequeue();
            T b = dataQueue.dequeue();
            BinaryTreeNode<T> parent = parentQueue.dequeue();
            if (a != null) {
                parent.setLeft(new BinaryTreeNode<T>(a));
                parentQueue.enqueue(parent.getLeft());
            }
            if (b != null) {
                parent.setRight(new BinaryTreeNode<T>(b));
                parentQueue.enqueue(parent.getRight());
            }
        }
        return tree;
    }
}
