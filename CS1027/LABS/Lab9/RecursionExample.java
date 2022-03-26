public class RecursionExample {

	private static int recursiveSum(int value) {
		if (value == 1) return 1;
		int result = recursiveSum(value - 1);
		return result + value;
	}
	
	public static void main(String[] args) {
		int limit = 10;
		
		int sum = recursiveSum(limit);
		System.out.println("The sum is "+sum);
	}

}
