import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JComponent;

public class Board extends JComponent {

	static final long serialVersionUID = 1;

	public Board() {
	}

	public void paint(Graphics display) {
		display.setColor(Color.lightGray);
	}
}