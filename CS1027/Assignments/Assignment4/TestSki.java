import java.util.Iterator;

public class TestSki {

	private static int[][] CORRECT_PATHS = new int[][] {
		new int[] {0, 2}, new int[] {0, 1, 3, 7}, new int[] {0, 2, 6, 13}, new int[] {0, 2, 6, 14}, new int[] {0, 1, 4, 10, 19}
	};
	
	public static void main(String[] args) {
		ArrayUnorderedList<SkiSegment> path; 
		String[] hill;
		Ski ski;
		
		
		
		// --------------- Test 1 ---------------
		
		hill = new String[] {"", "slalom-L", "jump-30"};
		ski = new Ski(hill);
		path = new ArrayUnorderedList<SkiSegment>();
		ski.skiNextSegment(ski.getRoot(), path);
		if (comparePaths(path.iterator(), 1)) {
			System.out.println("Test 1 Passed");
		} else {
			System.out.println("Test 1 Failed");
		}
		
		
		
		// --------------- Test 2 ---------------
		
		hill = new String[] {"", "jump-30", "slalom-W", "slalom-L", "slalom-W", "jump-20", "jump-40", "", null, "slalom-L", "jump-20", null, null, "slalom-L", "slalom-W"};
		ski = new Ski(hill);
		path = new ArrayUnorderedList<SkiSegment>();
		ski.skiNextSegment(ski.getRoot(), path);
		if (comparePaths(path.iterator(), 2)) {
			System.out.println("Test 2 Passed");
		} else {
			System.out.println("Test 2 Failed");
		}
		
		
		
		// --------------- Test 3 ---------------
		
		hill = new String[] {"", "jump-30", "jump-50", "slalom-L", "jump-20", "slalom-W", "", "", null, "slalom-L", "slalom-W", "jump-30", "", "", null};
		ski = new Ski(hill);
		path = new ArrayUnorderedList<SkiSegment>();
		ski.skiNextSegment(ski.getRoot(), path);
		if (comparePaths(path.iterator(), 3)) {
			System.out.println("Test 3 Passed");
		} else {
			System.out.println("Test 3 Failed");
		}
		
		
		
		// --------------- Test 4 ---------------
		
		hill = new String[] {"", "", "", "jump-40", "jump-40", "jump-40", "jump-40", "slalom-W", "", "slalom-W", "", "slalom-W", "", "slalom-W", ""};
		ski = new Ski(hill);
		path = new ArrayUnorderedList<SkiSegment>();
		ski.skiNextSegment(ski.getRoot(), path);
		if (comparePaths(path.iterator(), 4)) {
			System.out.println("Test 4 Passed");
		} else {
			System.out.println("Test 4 Failed");
		}
		
		
		
		// --------------- Test 5 ---------------
		
		hill = new String[] {"", "", "slalom-W", "slalom-L", "jump-30", "jump-50", "jump-20", "slalom-W", "", null, "slalom-W", "jump-30", "", null, null, "jump-30", "", null, null, "jump-30", "jump-20", null, null, "", "slalom-W"};
		ski = new Ski(hill);
		path = new ArrayUnorderedList<SkiSegment>();
		ski.skiNextSegment(ski.getRoot(), path);
		if (comparePaths(path.iterator(), 5)) {
			System.out.println("Test 5 Passed");
		} else {
			System.out.println("Test 5 Failed");
		}
		
	}
	
	
	public static void printPath (Iterator<SkiSegment> iter) {
		SkiSegment seg;
		while (iter.hasNext()) {
			seg = iter.next();
			System.out.print(seg.getID() + "  ");
		}
		System.out.println();
	}
	
	public static boolean comparePaths (Iterator<SkiSegment> iter, int testNo) {
		int[] correct = CORRECT_PATHS[testNo-1];
		SkiSegment seg;
		int s = 0;
		try {
			while (iter.hasNext()) {
				seg = iter.next();
				if (Integer.parseInt(seg.getID()) != correct[s++]) {
					return false;
				}
			}
		} catch (ArrayIndexOutOfBoundsException e) {
			return false;
		}
		return true;
	}
	
}
