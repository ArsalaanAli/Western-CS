
public class JumpSegment extends SkiSegment {
	
	private int height;
	
	public JumpSegment (String id, String label) {
		super(id, "jump");

		int hyphenPos = label.indexOf("-");
		String ht = label.substring(hyphenPos+1);
		this.height = Integer.parseInt(ht);
		
	}
	
	public int getHeight () {
		return height;
	}

}
