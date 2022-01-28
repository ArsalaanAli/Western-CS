public class TestDataTypes {

	public static void main(String[] args) {
		int[] testArray = { 2, 4, 6 }; // This statement creates an array of size 3 storing values 2, 4, and 6
		DataTypes data1 = new DataTypes(2, 3.3, 's', true, new ClassA(3, testArray));
		DataTypes data2 = new DataTypes(2, 3.3, 's', true, new ClassA(3, testArray));
		System.out.println("data1 == data2 is " + String.valueOf(data1 == data2));
		System.out.println("data1.intVar == data2.intVar is " + String.valueOf(data1.intVar == data2.intVar));
		System.out.println("data1.charVar == data2.charVar is " + String.valueOf(data1.charVar == data2.charVar));
		System.out.println("data1.boolVar == data2.boolVar is " + String.valueOf(data1.boolVar == data2.boolVar));
		System.out.println("data1.doubleVar == data2.doubleVar is " + String.valueOf(data1.doubleVar == data2.doubleVar));
		System.out.println("data1.varA == data2.varA is " + String.valueOf(data1.varA == data2.varA));
		System.out.println("data1.varA.numItems == data2.varA.numItems is " + String.valueOf(data1.varA.numItems == data2.varA.numItems));
		System.out.println("data1.varA.arrItems == data2.varA.arrItems is " + String.valueOf(data1.varA.arrItems == data2.varA.arrItems));

		// Test data1 == data2 

		// Test data1.intVar == data2.intVar

		// Test data1.charVar == data2.charVar

		// Test data1.boolVar == data2.boolVar

		// Test data1.doubleVar == data2.doubleVar

		// Test data1.varA == data2.varA

		// Test data1.varA.numItems == data2.varA.numItems
		
		// Test data1.varA.arrItems == data2.varA.arrItems		
	}

}
