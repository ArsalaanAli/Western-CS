import java.util.Iterator;

public class TestTreeBuilder {

	public static void main(String[] args) {
		String[] data;
		LinkedBinaryTree<String> tree;
		BinaryTreeNode<String> root;
		Iterator<String> iter;
		String str;
		TreeBuilder<String> tb = new TreeBuilder<String>();

		// --------------- Test 1 ---------------

		boolean test1Success = false;

		data = new String[] {"A","B","C","D","E","F","G"};

		tree = tb.buildTree(data);

		str = "";
		iter = tree.iteratorInOrder();
		while (iter.hasNext()) { str += iter.next(); }

		if (str.equals("DBEAFCG")) {
			test1Success = true;
		}

		if (test1Success) {
			System.out.println("Test 1 passed");
		} else {
			System.out.println("Test 1 failed");
		}


		// --------------- Test 2 ---------------

		boolean test2Success = false;

		data = new String[] {"A","B","C","D","E","F","G","H","I"};

		tree = tb.buildTree(data);

		str = "";
		iter = tree.iteratorInOrder();
		while (iter.hasNext()) { str += iter.next(); }

		if (str.equals("HDIBEAFCG")) {
			test2Success = true;
		}

		if (test2Success) {
			System.out.println("Test 2 passed");
		} else {
			System.out.println("Test 2 failed");
		}

		// --------------- Test 3 ---------------

		boolean test3Success = false;

		data = new String[] {"A","B",null,"C",null,"D","E",null,null,"F","G"};
		tree = tb.buildTree(data);

		str = "";
		iter = tree.iteratorInOrder();
		while (iter.hasNext()) { str += iter.next(); }
		
		if (str.equals("DCFEGBA")) {
			test3Success = true;
		}

		if (test3Success) {
			System.out.println("Test 3 passed");
		} else {
			System.out.println("Test 3 failed");
		}


		// --------------- Test 4 ---------------

		boolean test4Success = false;

		data = new String[] {"A",null,"B","C",null};
		tree = tb.buildTree(data);

		try {
			root = tree.getRoot();
			if (root.getData().equals("A") && root.getLeft() == null && root.getRight().getData().equals("B")
					&& root.getRight().getLeft().getData().equals("C") && root.getRight().getRight() == null) {
				test4Success = true;
			}
		} catch (Exception e) {
			test4Success = false;
		}

		if (test4Success) {
			System.out.println("Test 4 passed");
		} else {
			System.out.println("Test 4 failed");
		}

		// --------------- Test 5 ---------------

		boolean test5Success = false;

		Integer[] iData = new Integer[] {5,9,18,null,null,3,10};
		
		TreeBuilder<Integer> builder = new TreeBuilder<Integer>();
		LinkedBinaryTree<Integer> iTree = builder.buildTree(iData);
		BinaryTreeNode<Integer> iRoot;
		
		try {
			iRoot = iTree.getRoot();
			if (iRoot.getData() == 5 && iRoot.getLeft().getData() == 9 && iRoot.getRight().getData() == 18
					&& iRoot.getLeft().getLeft() == null && iRoot.getLeft().getRight() == null &&
					iRoot.getRight().getLeft().getData() == 3 && iRoot.getRight().getRight().getData() == 10) {
				test5Success = true;
			}
		} catch (Exception e) {
			test5Success = false;
		}

		if (test5Success) {
			System.out.println("Test 5 passed");
		} else {
			System.out.println("Test 5 failed");
		}

	}

}