
public class CountObjects {

	public static void main(String[] args) {
		int numObjects;
		ClassC C = null;
		for (int i = 0; i < RandomNumber.getRandomNumber(10, 20); ++i)
			C = new ClassC();
		numObjects = -1;
		System.out.println("Number of objects created is " + numObjects);
	}

}
