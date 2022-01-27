/**
 * This class represents a player on a hockey team. Each player has a name, position and jersey number.
 * @author Arsalaan Ali
 */

public class Player{
	private String name, position;
	private int jerseyNum;

	public Player(String name, String position, int jerseyNum) {
		/*
		This is the constructor so we will be
		initializing the member variables here
		*/
		/**
		* Constructor creates a Player with name, position, and jersey number
		* @param name name of the player
		* @param position the players position
		* @param jerseyNum the players jersey number
		*/
		this.name = name;
		this.position = position;
		this.jerseyNum = jerseyNum;
	}
	/*
	* accesor method to return the players name
	* @return name of the player
	*/
	public String getName() {
		// Get the player's name.
		
		return this.name;
	}
	/*
	* accesor method to set the player's name
	* @param name new name that you want to set
	*/
	public void setName(String name) {
		this.name = name;
	}

	public String getPosition() {
		return this.position;
	}

	public void setPosition(String position) {
		this.position = position;
	}

	public int getJerseyNum() {
		return this.jerseyNum;
	}

	public void setJerseyNum(int jerseyNum) {
		this.jerseyNum = jerseyNum;
	}

	public String toString() {
		return this.name + ": #" + this.jerseyNum;
	}

	public boolean equals(Player other) {
		return this.name.equals(other.name) && this.jerseyNum == other.getJerseyNum();
	}
	
}