
public class TestEquals {

	public static void main(String[] args) {
		int[] arr1 = { 1, 2, 3 };
		int[] arr2 = { 3, 2, 1 };
		int[] arr3 = { 1, 2, 3 };
		DataTypes data1 = new DataTypes(2, 2.3, 'a', false, new ClassA());
		DataTypes data2 = new DataTypes(2, 2.3, 'a', false, new ClassA());
		DataTypes data3 = new DataTypes(2, 2.3, 'a', false, new ClassA(3, arr1));
		DataTypes data4 = new DataTypes(2, 2.3, 'a', false, new ClassA(3, arr2));
		DataTypes data5 = new DataTypes(2, 2.3, 'f', true, new ClassA(3, arr2));
		DataTypes data6 = new DataTypes(2, 2.3, 'a', false, new ClassA(3, arr3));

		if (data1.equals(data2))
			System.out.println("Test 1 passed");
		else
			System.out.println("Test 1 failed");

		if (data3.equals(data6))
			System.out.println("Test 2 passed");
		else
			System.out.println("Test 2 failed");

		if (!data3.equals(data4))
			System.out.println("Test 3 passed");
		else
			System.out.println("Test 3 failed");

		if (!data4.equals(data5))
			System.out.println("Test 4 passed");
		else
			System.out.println("Test 4 failed");
	}

}
