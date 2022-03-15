
public class Snail {
	
	public static char icon = '@';
	private int position;
	private QueueADT<Integer> movePattern;
	
	public Snail (int[] pattern) {
		this.position = 0;
		this.movePattern = new LinkedQueue<Integer>();
		for (int i = 0; i < pattern.length; i++) {
			movePattern.enqueue(pattern[i]);
		}
	}
	
	public void move() {
		int step = movePattern.dequeue();
		movePattern.enqueue(step);
		position += step;
		position = Math.min(position, SnailRace.raceLength);
	}
	
	public int getPosition () {
		return position;
	}
	
	public void display () {
		int dashesBefore = position, dashesAfter = SnailRace.raceLength - position;
		for (int i = 0; i < dashesBefore; i++) {
			System.out.print("-");
		}
		System.out.print("@");
		for (int i = 0; i < dashesAfter; i++) {
			System.out.print("-");
		}
		System.out.println();
	}
}
