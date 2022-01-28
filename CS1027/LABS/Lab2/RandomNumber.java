import java.util.Random;

public class RandomNumber {
	
	private static int seed = 123456789;
	private static Random rnd = new Random(seed);
	
	/**
	 * Generate a random integer between min and max (inclusive)
	 * @param min: the minimum value in the range for the random number (inclusive)
	 * @param max: the maximum value in the range for the random number (inclusive)
	 * @return random integer within the range min-max (inclusive)
	 */
	public static int getRandomNumber (int min, int max) {
		int num = rnd.nextInt(max-min+1) + min;
		return num;
	}

}
