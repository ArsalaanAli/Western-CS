
public class ExecutionStackExample {

	private static void m1(char param1) {
		int local1;
		if (param1 == '0') local1 = 0;
		else {
			local1 = 1;
			System.out.println("Pause execution here");			
		}
	}
	
	private static int m2(String param2) {
		param2 = param2 + ".txt";
		m1 (param2.charAt(0));
		return param2.length();
	}
	
	private static void m3 (int[] param3, int i) {
		int value = m2(""+i);
		if (param3[i] > 0) m3(param3,i+1);
		else param3[i] = -value;
		System.out.println("Pause execution here");
	}
	
	public static void main(String[] args) {
		int[] local2 = {3,0};
		m3 (local2,0);
	}

}
