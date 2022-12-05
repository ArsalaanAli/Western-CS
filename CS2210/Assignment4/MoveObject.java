
public class MoveObject {

	private Gui environment; // Graphical user interface

	/* =========================== */
	public MoveObject(Gui env) {
		/* =========================== */
		environment = env;
	}

	/* ============================================ */
	public int moveLeft(MyObject[] figs, int numFigures, int fignum, int step)
	/* ============================================ */
	/*
	 * Move the graphical object specified by the second argument to the left. Return true
	 * if the graphical object could move.
	 */
	{
		Location curr, next;
		int newx;

		curr = figs[fignum].getLocus();
		if (curr.getx() < step)
			return -1; // Graphical object reached left border
		else
			newx = curr.getx() - step;
		next = new Location(newx, curr.gety());

		// Verify that graphical obejcts do not overlap
		figs[fignum].setLocus(next);
		for (int i = 0; i < numFigures; ++i)
			if ((i != fignum) && (figs[fignum].intersects(figs[i]))) {
				figs[fignum].setLocus(curr);
				return i;
			}

		// Move graphical object to its new Location
		figs[fignum].setLocus(curr);
		environment.eraseFigure(figs[fignum]);
		figs[fignum].setLocus(next);
		environment.drawFigure(figs[fignum]);
		return -2;
	}

	/* ============================================ */
	public int moveRight(MyObject[] figs, int numFigures, int fignum, int step)
	/* ============================================ */
	/*
	 * Move the graphical object specified by the second argument to the right. Return true
	 * if the graphical obejct could move.
	 */
	{
		Location curr, next;
		int newx;

		curr = figs[fignum].getLocus();
		if (curr.getx() > (environment.displayWidth() - figs[fignum].getWidth() - step))
			return -1; // Graphical object reached right border
		else
			newx = curr.getx() + step;
		next = new Location(newx, curr.gety());

		// Check that graphical objects do not overlap
		figs[fignum].setLocus(next);
		for (int i = 0; i < numFigures; ++i)
			if ((i != fignum) && (figs[fignum].intersects(figs[i]))) {
				figs[fignum].setLocus(curr);
				return i;
			}

		// Move graphical object to its new Location
		figs[fignum].setLocus(curr);
		environment.eraseFigure(figs[fignum]);
		figs[fignum].setLocus(next);
		environment.drawFigure(figs[fignum]);
		return -2;
	}

	/* ============================================ */
	public int moveDown(MyObject[] figs, int numFigures, int fignum, int step)
	/* ============================================ */
	/*
	 * Move the graphical object specified by the second argument t the right. Return true
	 * if the graphical object could move.
	 */
	{
		Location curr, next;
		int newy;

		curr = figs[fignum].getLocus();
		if (curr.gety() > (environment.displayHeight() - figs[fignum].getHeight() - step))
			return -1; // Graphical object reached bottom border
		else
			newy = curr.gety() + step;
		next = new Location(curr.getx(), newy);

		// Check that graphical objects do not overlap
		figs[fignum].setLocus(next);
		for (int i = 0; i < numFigures; ++i)
			if ((i != fignum) && (figs[fignum].intersects(figs[i]))) {
				figs[fignum].setLocus(curr);
				return i;
			}

		// Move graphical object to its new Location
		figs[fignum].setLocus(curr);
		environment.eraseFigure(figs[fignum]);
		figs[fignum].setLocus(next);
		environment.drawFigure(figs[fignum]);
		return -2;
	}

	/* ============================================ */
	public int moveUp(MyObject[] figs, int numFigures, int fignum, int step)
	/* ============================================ */
	/*
	 * Move the graphical object specified by the second argument to the right. Return true
	 * if the graphical object could move
	 */
	{
		Location curr, next;
		int newy;

		curr = figs[fignum].getLocus();
		if (curr.gety() < step)
			return -1; // Graphical object reached top border
		else
			newy = curr.gety() - step;
		next = new Location(curr.getx(), newy);

		// Check that graphical objects do not overlap
		figs[fignum].setLocus(next);
		for (int i = 0; i < numFigures; ++i)
			if ((i != fignum) && (figs[fignum].intersects(figs[i]))) {
				figs[fignum].setLocus(curr);
				return i;
			}

		// Draw graphical object in its new Location
		figs[fignum].setLocus(curr);
		environment.eraseFigure(figs[fignum]);
		figs[fignum].setLocus(next);
		environment.drawFigure(figs[fignum]);
		return -2;
	}
}