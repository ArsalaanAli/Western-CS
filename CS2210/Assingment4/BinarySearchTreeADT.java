public interface BinarySearchTreeADT {

	/*
	 * Returns the root of the binary search tree
	 */
	public BNode getRoot();

	/*
	 * Returns the Pel object storing the given key, if the key is stored in
	 * the tree. Returns null otherwise.
	 */
	public Pel get(BNode r, Location key);

	/*
	 * Inserts the given data in the tree if no data item with the same key is
	 * already there. If a node already stores the same key, the algorithm
	 * throws a DuplicatedKeyException.
	 */
	public void put(BNode r, Pel data) throws DuplicatedKeyException;

	/*
	 * Removes the data item with the given key, if the key is stored in the
	 * tree. Throws an InexistentKeyException otherwise.
	 */
	public void remove(BNode r, Location key) throws InexistentKeyException;

	/*
	 * Returns the Pel object with the smallest key larger than the given one (note
	 * that the tree does not need to store a node with the given key). Returns
	 * null if the given key has no successor.
	 */
	public Pel successor(BNode r, Location key);

	/*
	 * Returns the Pel object with the largest key smaller than the given one (note
	 * that the tree does not need to store a node with the given key). Returns
	 * null if the given key has no predecessor.
	 */
	public Pel predecessor(BNode r, Location key);

	/*
	 * Returns the Pel object with the smallest key. Throws an EmptyTreeException if
	 * the tree is empty.
	 */
	public Pel smallest(BNode r) throws EmptyTreeException;

	/*
	 * Returns the Pel object with the largest key. Throws an EmptyTreeException if
	 * the tree is empty.
	 */
	public Pel largest(BNode r) throws EmptyTreeException;
}