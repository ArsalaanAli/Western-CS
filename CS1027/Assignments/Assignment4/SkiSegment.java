
public class SkiSegment {
	
	private String ID;
	private String type;
	
	/**
	 * Trail constructor
	 * @param id
	 * @param type
	 */
	public SkiSegment (String id, String type) {
		this.ID = id;
		this.type = type;
	}
	
	public String getID() {
		return ID;
	}

	public String toString () {
		return type + " " + ID;
	}
	
}
