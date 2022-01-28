public class ClassB {

	private int counter = 0;

	public ClassB() {
		counter = 1;
	}

	public void incCounter() {
		++counter;
	}

	public int getCounter() {
		return counter;
	}

	public static void main(String[] args) {
		ClassB test = new ClassB();
		int i = test.getCounter();
		test.incCounter();
		System.out.println("i = " + i + " counter = " + test.getCounter());
	}
}
