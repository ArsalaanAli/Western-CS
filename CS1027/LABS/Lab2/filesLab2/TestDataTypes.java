public class TestDataTypes {

	public static void main(String[] args) {
		int[] testArray = { 2, 4, 6 }; // This statement creates an array of size 3 storing values 2, 4, and 6
		DataTypes data1 = new DataTypes(2, 3.3, 's', true, new ClassA(3, testArray));
		DataTypes data2 = new DataTypes(2, 3.3, 's', true, new ClassA(3, testArray));

		// Test data1 == data2

		// Test data1.intVar == data2.intVar

		// Test data1.charVar == data2.charVar

		// Test data1.boolVar == data2.boolVar

		// Test data1.doubleVar == dta2.doubleVar

		// Test data1.varA == data2.varA

		// Test data1.varA.numItems == data2.varA.numItems
		
		// Test data1.varA.arrItems == data2.varA.arrItems		
	}

}
