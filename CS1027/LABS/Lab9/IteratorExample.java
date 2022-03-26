import java.util.*;

public class IteratorExample {

	private static Object[] collections;
	private static Random rand = new Random (1000);
	
	// Initialize the collections with random values
	private static void initialize(ArrayList<Integer> list1, HashSet<Integer> list2, LinkedList<Integer> list3, TreeSet<Integer> list4, Vector<Integer> list5) {
		int i;
		int size = rand.nextInt(20);
		for (i = 0; i < size; ++i) {
			list1.add(rand.nextInt(1000));
			list2.add(rand.nextInt(1000));
			list3.add(rand.nextInt(1000));	
			list4.add(rand.nextInt(1000));	
			list5.add(rand.nextInt(1000));				
		}
	}
	
	// Initialize the array of collections of different types
	private static void initializeCollections() {
		ArrayList<Integer> list1 = new ArrayList<Integer>();
		HashSet<Integer> list2 = new HashSet<Integer>();
		LinkedList<Integer> list3 = new LinkedList<Integer>();
		TreeSet<Integer> list4 = new TreeSet<Integer>();
		Vector<Integer> list5 = new Vector<Integer>();
		initialize(list1,list2,list3,list4,list5);
		collections = new Object[5];
		collections[0] = list1;
		collections[1] = list2;
		collections[2] = list3;
		collections[3] = list4;
		collections[4] = list5;
	}
	
	// Check that the code produces the correct answer
	private static void check(int largestValue) {
		int res = (int)Math.log10(Math.sqrt(largestValue + 37)*3+4);
		if (res == 2) System.out.println("Test passed");
		else System.out.println("Test failed");
	}
	
	public static void main(String[] args) {
		int largestValue = 0;		
		initializeCollections();
        // Add code here to compute the largest value stored in array "collections"
		// and store this value in variable largestValue
		Iterator<Integer> iter;
		for (int i = 0; i < 5; i++) {
			iter = ((AbstractCollection<Integer>)collections[i]).iterator();
			while (iter.hasNext()) {
				int x = iter.next();
				largestValue = Math.max(x, largestValue);
			}
		}
		
		// Do not modify the following code
		check(largestValue);
	}

}
