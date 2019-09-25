/**
 * CS2210A Assignment 4
 * @author Jameel Kaba (jkaba) Student #: 250796017
 * 
 * This class represents a data item to be stored 
 * in a Binary Search Tree
 */

public class DictEntry {

	// private variables
	private Position p;
	private int color;

	/**
	 * DictEntry constructor that returns a DictEntry with a
	 * user specified position and color
	 * @param p The position (key) of the DictEntry
	 * @param color The color of the DictEntry
	 */
	public DictEntry(Position p, int color){
		this.p = p;
		this.color = color;
	}

	/**
	 * Getter method that returns the position (key) of the DictEntry
	 * @return p
	 */
	public Position getPosition(){
		return p;
	}

	/**
	 * Getter method that returns the color value of the DictEntry
	 * @return color
	 */
	public int getColor(){
		return color;
	}

}
