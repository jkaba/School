/**
 * CS2210A Assignment 4
 * @author Jameel Kaba (jkaba) Student #: 250796017
 * 
 * This class represents Nodes of a Binary Search Tree
 * that hold/store a data item.
 */

public class BinaryTreeNode {

	// private variables
	private BinaryTreeNode parent, left, right;
	private DictEntry element;
	private int height;

	/**
	 * Binary Tree Node Constructor that returns a Binary Tree Node
	 * with a specified DictEntry as it's element
	 * @param element The DictEntry stored in the node
	 */
	public BinaryTreeNode(DictEntry element){
		this.element = element;
		this.height = 0;
		this.left = null;
		this.right = null;
		this.parent = null;
	}

	/**
	 * Getter method that returns the parent of the node
	 * @return parent
	 */
	public BinaryTreeNode getParent(){
		return parent;
	}

	/**
	 * Setter method that sets the parent node to a user specified node
	 * @param parent The new parent of the node
	 */
	public void setParent(BinaryTreeNode parent){
		this.parent = parent;
	}

	/**
	 * Getter method that gets the left child of the node
	 * @return left 
	 */
	public BinaryTreeNode getLeft(){
		return left;
	}

	/**
	 * Setter method that sets the left child of the node to a user specified node
	 * @param left The new left child of the node
	 */
	public void setLeft(BinaryTreeNode left){
		this.left = left;
	}

	/**
	 * Getter method that gets the right child of the node
	 * @return right
	 */
	public BinaryTreeNode getRight(){
		return right;
	}

	/**
	 * Setter method that sets the right child to a user specified node
	 * @param right The new right child of the node
	 */
	public void setRight(BinaryTreeNode right){
		this.right = right;
	}

	/**
	 * Getter method that gets the DictEntry Element of the node
	 * @return element
	 */
	public DictEntry getElement(){
		return element;
	}

	/**
	 * Setter method that sets the DictEntry Element of the node
	 * @param element The DictEntry to be stored in the node
	 */
	public void setElement(DictEntry element){
		this.element = element;
	}

	/**
	 * Setter method that sets the Height of the node/tree
	 * @param height The height of the tree
	 */
	public void setHeight(int height){
		this.height = height;
	}

	/**
	 * Getter method that gets the Height of the node/tree
	 * @return height
	 */
	public int getHeight(){

		// if the root is a leaf return 0
		if(this.left == null && this.right == null){
			return 0;
		}

		else{

			// Call getHeight on both the left and right child
			int left = this.left.getHeight();
			int right = this.right.getHeight(); 

			// if the right side is longer than the left side
			if (right >= left){

				// return 1 plus the value from the right
				return 1 + right;
			}

			// else if the left side is longer than the right side
			else {

				// return 1 plus the value from the left
				return 1 + left;
			}
		}
	}

}