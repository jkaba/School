/**
 * CS2210A Assignment 4
 * @author Jameel Kaba (jkaba) Student #: 250796017
 * 
 * This class represents the position (x, y) of a pixel
 */

public class Position {

	//private variables
	private int x;
	private int y;

	/**
	 * Position constructor that returns a new position with the
	 * specified coordinates
	 * @param x The position's x coordinate
	 * @param y The position's y coordinate
	 */
	public Position(int x, int y){
		this.x = x;
		this.y = y;
	}

	/**
	 * Getter method that returns the x coordinate of a position
	 * @return x
	 */
	public int getX(){
		return x;
	}

	/**
	 * Getter method that returns the y coordinate of a position
	 * @return Y
	 */
	public int getY(){
		return y;
	}

	/**
	 * Compares this Position with Position p using row-order
	 * @param p
	 * @return
	 */
	public int compareTo(Position p){

		// if this position is greater than position p then return 1
		if((this.getY() > p.getY()) || (this.getY() == p.getY() && this.getX() > p.getX())){
			return 1;
		} 

		// else if the two positions are equal then return 0
		else if(this.getY() == p.getY() && this.getX() == p.getX()){
			return 0;
		} 

		// if this case is reached then position p is greater than this position 
		else{
			// in this case return -1
			return -1;
		}
	}
}

