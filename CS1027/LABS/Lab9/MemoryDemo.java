public class MemoryDemo {
	
	public static int m1(int x) {
		x = 3;
		return x;
	} 
	
	public static void m2(int[] arr) {
		arr[0] = 3;
	} 

	public static void m3(int a0) {
		int[] arr = new int[2];
		arr[1] = a0 + m1(a0);
	}
	
	public static void main(String[] args) {
		int x = 2;
		m1(x);
		// What is the value of x here?
		System.out.println(x);
		int[] arr = {5, 6};
		m2(arr);
		// What is the value of arr[0] here?
		System.out.println(arr[0]);
		m3(arr[1]);
		// What is the value of arr[1] here?
		System.out.println(arr[1]);
	} //end main
} //end MemoryDemo