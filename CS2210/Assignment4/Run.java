import java.util.Random;

public class Run {

	private static MyObject[] figures; // Data structure to store icons
	private static Gui window;
	private static final String MOBILE_FIGURE = "user";// MyObject that can be
														// moved by user
	private static final String FIGURE_KILLED = "killed";// MyObject destroyed
	private static final int SUCCESS = -2; // MyObject was successfully moved
	private static final int HIT_BORDER = -1; // MyObject could not move as it
	// hit the window's border

	/* ====================================== */
	public static void main(String args[]) {
		/* ====================================== */

		int numberFigures;
		final String progType = "computer"; // Type of icons controlled by
											// the computer
		final int left = 0; // Movement directions
		final int right = 1;
		final int up = 2;

		int ncomp; // Number of icons controlled by the computer
		int[] progFig; // MyObjects controlled by computer
		int[] dir; // Direction in which computer icons move

		Random generator = new Random();
		int code;
		int step = 4; // Length in pixels of each movement of a icon
		MoveObject mover;

		if (args.length == 3)
			// Arguments include input file and window width and height
			try {
				window = new Gui(Integer.parseInt(args[1]), Integer.parseInt(args[2]), args[0]);
			} catch (Exception e) {
				window = new Gui(500, 500, args[0]);
			}
		else
			window = new Gui(500, 500, args[0]); // Set up drawing environment
		mover = new MoveObject(window); // and read input icons
		figures = window.getFigures();
		numberFigures = window.getNumFigures();
		progFig = new int[numberFigures];
		dir = new int[numberFigures];

		// Determine the icons controlled by the program
		ncomp = 0;
		for (int i = 0; i < numberFigures; ++i) {
			if (figures[i].getType().equals(progType)) {
				dir[ncomp] = generator.nextInt(3);// Choose random direction
													// for movement of objects

				progFig[ncomp] = i;
				ncomp++;
			}
		}

		// Move objects randomly
		while (true) {
			for (int i = 0; i < ncomp; ++i) {
				if (dir[i] == left) {
					if ((code = mover.moveLeft(figures, numberFigures, progFig[i], step)) != SUCCESS)
						dir[i] = resolveCollision(code, dir[i]);
					else
						System.out.println("Enemy Moved");
				} else if (dir[i] == right) {
					if ((code = mover.moveRight(figures, numberFigures, progFig[i], step)) != SUCCESS)
						dir[i] = resolveCollision(code, dir[i]);
					else
						System.out.println("Enemy Moved");
				} else if (dir[i] == up) {
					if ((code = mover.moveUp(figures, numberFigures, progFig[i], step)) != SUCCESS)
						dir[i] = resolveCollision(code, dir[i]);
					else
						System.out.println("Enemy Moved");
				} else {
					if ((code = mover.moveDown(figures, numberFigures, progFig[i], step)) != SUCCESS)
						dir[i] = resolveCollision(code, dir[i]);
					else
						System.out.println("Enemy Moved");
				}
			}
			if (window.Wait())
				++step;
		}

	}

	/* ======================================================= */
	private static int resolveCollision(int code, int dir) {
		/* ======================================================= */
		// Determine direction in which icon will next move. Delete
		// icons that have been destroyed.

		Random generator = new Random();

		if ((code != HIT_BORDER) && (figures[code].getType().equals(MOBILE_FIGURE))) {
			/* Kill figure */
			try {
				// Erase object. Object will blink 5 times
				for (int i = 0; i < 5; ++i) {
					window.drawFigure(figures[code]);
					Thread.sleep(200);
					window.eraseFigure(figures[code]);
					Thread.sleep(200);
				}

				figures[code].setLocus(new Location(-1000, -1000));
				figures[code].setType(FIGURE_KILLED);
			} catch (Exception e) {
				System.out.println(e.getMessage());
			}
		}

		return (dir + generator.nextInt(3)) % 4;
	}
}