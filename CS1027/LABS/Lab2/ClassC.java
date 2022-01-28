public class ClassC {

	public static int counter = 0;

	public ClassC() {
		counter++;
	}

	public void incCounter() {
		++counter;
	}

	public int getCounter() {
		return counter;
	}

}
