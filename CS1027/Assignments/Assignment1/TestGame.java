
public class TestGame {

	public static void main(String[] args) {
		
		Yahtzee game1, game2, game3;
		
		game1 = new Yahtzee();
		game2 = new Yahtzee(new Dice[] {new Dice(2), new Dice(5), new Dice(3), new Dice(5), new Dice(6)});
		game3 = new Yahtzee(new Dice[] {new Dice(6), new Dice(1), new Dice(1), new Dice(5), new Dice(2)});

		
		// Test 1 - constructors and toString
		
		if (game1.toString().equals("Dice: {2, 1, 6, 5, 1}")) {
			System.out.println("Test 1 Passed");
		} else {
			System.out.println("Test 1 Failed");
		}

		
		// Test 2 - constructors and toString
		
		if (game2.toString().equals("Dice: {2, 5, 3, 5, 6}")) {
			System.out.println("Test 2 Passed");
		} else {
			System.out.println("Test 2 Failed");
		}
		
		
		// Test 3 - equals

		if (!game1.equals(game2)) {
			System.out.println("Test 3 Passed");
		} else {
			System.out.println("Test 3 Failed");
		}
		
		
		// Test 4 - equals
		
		if (game1.equals(game3)) {
			System.out.println("Test 4 Passed");
		} else {
			System.out.println("Test 4 Failed");
		}
		
		
		// Test 5 - getValueCount

		if (showArray(game1.getValueCount()).equals("[2, 1, 0, 0, 1, 1]")) {
			System.out.println("Test 5 Passed");
		} else {
			System.out.println("Test 5 Failed");
		}
		
		
		// Test 6 - getValueCount
		
		game3 = new Yahtzee();
		if (showArray(game3.getValueCount()).equals("[0, 2, 0, 1, 1, 1]")) {
			System.out.println("Test 6 Passed");
		} else {
			System.out.println("Test 6 Failed");
		}
		
		
		// Test 7 - getScoreOptions
		
		game1 = new Yahtzee(new Dice[] {new Dice(5), new Dice(3), new Dice(5), new Dice(5), new Dice(4)});
		if (showArray(game1.getScoreOptions()).equals("[0, 0, 3, 4, 15, 0, 22, 0, 0, 0, 0, 0, 22]")) {
			System.out.println("Test 7 Passed");
		} else {
			System.out.println("Test 7 Failed");
		}
		
		
		// Test 8 - getScoreOptions
		
		game1 = new Yahtzee(new Dice[] {new Dice(4), new Dice(4), new Dice(4), new Dice(4), new Dice(4)});
		if (showArray(game1.getScoreOptions()).equals("[0, 0, 0, 20, 0, 0, 20, 20, 0, 0, 0, 50, 20]")) {
			System.out.println("Test 8 Passed");
		} else {
			System.out.println("Test 8 Failed");
		}
		
		
		// Test 9 - getScoreOptions
		
		game2 = new Yahtzee(new Dice[] {new Dice(1), new Dice(3), new Dice(1), new Dice(3), new Dice(3)});
		if (showArray(game2.getScoreOptions()).equals("[2, 0, 9, 0, 0, 0, 11, 0, 25, 0, 0, 0, 11]")) {
			System.out.println("Test 9 Passed");
		} else {
			System.out.println("Test 9 Failed");
		}

		
		// Test 10 - getScoreOptions
		
		game3 = new Yahtzee(new Dice[] {new Dice(4), new Dice(5), new Dice(5), new Dice(6), new Dice(3)});
		if (showArray(game3.getScoreOptions()).equals("[0, 0, 3, 4, 10, 6, 0, 0, 0, 30, 0, 0, 23]")) {
			System.out.println("Test 10 Passed");
		} else {
			System.out.println("Test 10 Failed");
		}
		
		
		// Test 11 - score
		
		game2 = new Yahtzee();
		if (showArray(game2.score()).equals("[21, 12]")) {
			System.out.println("Test 11 Passed");
		} else {
			System.out.println("Test 11 Failed");
		}
		
		
		// Test 12 - score
		
		game3 = new Yahtzee(new Dice[] {new Dice(4), new Dice(5), new Dice(1), new Dice(2), new Dice(3)});
		if (showArray(game3.score()).equals("[40, 10]")) {
			System.out.println("Test 12 Passed");
		} else {
			System.out.println("Test 12 Failed");
		}
		
		// Test 13 - score
		
		for (int i = 0; i < 4; i++) game3 = new Yahtzee();
		if (showArray(game3.score()).equals("[15, 6]")) {
			System.out.println("Test 13 Passed");
		} else {
			System.out.println("Test 13 Failed");
		}
		
	}
	
	public static String showArray (int[] arr) {
		String s = "[";
		for (int i = 0; i < arr.length; i++) {
			s += arr[i];
			if (i < arr.length - 1) s += ", ";
		}
		s += "]";
		return s;
	}

}
