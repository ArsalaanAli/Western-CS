
public class TestQueue {

	public static void main(String[] args) {
		
		LinkedQueue<String> Q = new LinkedQueue<String>();
		
		if (Q.isEmpty()) {
			System.out.println("Test 1 passed - isEmpty()");
		} else {
			System.out.println("Test 1 failed - isEmpty()");
		}
		
		Q.enqueue("one");
		Q.enqueue("two");
		Q.enqueue("three");
		Q.enqueue("four");
		Q.enqueue("five");
		Q.enqueue("six");
		Q.enqueue("seven");
		Q.enqueue("eight");
		Q.enqueue("nine");
		
		if (Q.size() == 9) {
			System.out.println("Test 2 passed - size()");
		} else {
			System.out.println("Test 2 failed - size()");
		}
		
		
		String firstElem = Q.first();
		if (firstElem.equals("one")) {
			System.out.println("Test 3 passed - first()");
		} else {
			System.out.println("Test 3 failed - first()");
		}
		
		// Dequeue several elements.
		for (int i = 0; i < 5; i++) {
			Q.dequeue();
		}
		
		firstElem = Q.first();
		if (firstElem.equals("six")) {
			System.out.println("Test 4 passed - first()");
		} else {
			System.out.println("Test 4 failed - first()");
		}

	}

}
