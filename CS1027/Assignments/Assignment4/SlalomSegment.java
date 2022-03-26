
public class SlalomSegment extends SkiSegment {
	
	private String dir;
	
	public SlalomSegment (String id, String label) {
		super(id, "slalom");
		
		int dirPos = label.indexOf("-");
		String dir = label.substring(dirPos+1);
		this.dir = dir;
	}
	
	public String getDirection () {
		return dir;
	}

}
