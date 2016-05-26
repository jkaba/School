/**
 * CS2210A Assignment 5
 * @author Jameel Kaba (jkaba) Student #: 250796017
 * 
 * Node class that represents the nodes on a graph
 */
public class Node {

	// Private variables
	private int nodeName;
	private boolean checkMark = false;

	/**
	 * Constructor that creates an unmarked node with name given by 
	 * the passed parameter
	 * @param name The name of the node
	 */
	public Node(int name) {
		nodeName = name;
		checkMark = false;
	}

	/**
	 * Setter method that sets the mark of a node to a specified
	 * mark either True or False
	 * @param Mark True or False the new mark of a node
	 */
	public void setMark(boolean mark) {
		checkMark = mark;
	}

	/**
	 * Getter method that returns the mark of a node 
	 * @return Mark of the node either True or False
	 */
	public boolean getMark() {
		return checkMark;
	}

	/**
	 * Getter method that gets the name of the node
	 * @return Name of the node
	 */
	public int getName() {
		return nodeName;
	}

}
