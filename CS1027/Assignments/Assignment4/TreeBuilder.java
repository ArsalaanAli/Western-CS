public class TreeBuilder {
    public LinkedBinaryTree<T> buildTree(T[] data) {
        LinkedQueue<T> dataQueue = new LinkedQueue<T>();
        LinkedQueue<BinaryTreeNode<T>> parentQueue = new LinkedQueue<BinaryTreeNode<T>>();
        for (T cur : data) {
            dataQueue.enqueue(cur);
        }
        
    }
}
