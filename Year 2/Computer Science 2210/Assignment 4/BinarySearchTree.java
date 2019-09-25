/**
 * CS2210A Assignment 4
 * @author Jameel Kaba (jkaba) Student #: 250796017
 * 
 * This class represents an ordered dictionary using a 
 * Binary Search Tree with each node referencing a DictEntry 
 */
public class BinarySearchTree implements BinarySearchTreeADT{

	// private variables
	private BinaryTreeNode root;				
	private int numElem;							

	/**
	 * Constructor method that returns a Binary Search Tree with 0 elements and
	 * the root set to null
	 */
	public BinarySearchTree(){
		this.numElem = 0;
		this.root = null;
	}

	/**
	 * find method that calls a helper method to search for a specified position 
	 * @param key The position to be found
	 */
	public DictEntry find(Position key) {
		BinaryTreeNode findNode = search(this.root, key);
		if(findNode != null){
			return findNode.getElement();
		} 
		else {
			return null;
		}
	}	

	/**
	 * Recursive Helper method that searches elements of a tree starting at a specified root and 
	 * searches for a specified position
	 * @param root The starting element for the search
	 * @param key The key/position that is being searched for
	 * @return null if root is null,
	 * @return the root if the position we are looking for is in the root
	 * @return recursive call that searches for the position in the rest of the tree
	 */
	private BinaryTreeNode search(BinaryTreeNode root, Position key){

		// if the root is null then return null
		if (root == null){
			return null;
		} 

		// create a position that contains the position stored in the root
		Position comparePos = root.getElement().getPosition();

		// if the compare position is the same as the key/position we are looking for
		if(comparePos.compareTo(key) == 0){

			// return the root 
			return root;
		} 

		// else if the compare position is less than the one we are looking for
		else if (comparePos.compareTo(key) == -1){

			// return a recursive call for the method called on the right child
			return search(root.getRight(), key);
		} 

		// else if the compare position is greater than the one we are looking for
		else{

			// return a recursive call for the method called on the left child
			return search(root.getLeft(), key);
		}
	}

	/**
	 * Insert method that inserts a specified element into the Binary Search Tree
	 * throws an exception if the element is in the tree
	 * @param element The element to be added into the tree
	 */
	public void insert(DictEntry element) throws BSTException {

		//create a temp node that contains the element to be added
		BinaryTreeNode insertNode = new BinaryTreeNode(element);

		// create a position to be searched for that contains the position of the element
		Position insertPos = element.getPosition();

		// if the position is found in the tree
		if(find(insertPos) != null){

			// throw an exception
			throw new BSTException("ERROR 404: Entry already exists");
		}

		// if the tree is empty
		if (this.isEmpty()) {

			// then set the root to the temp node
			this.root = insertNode;
		} 


		else {

			// create a node "current node" that references the root
			BinaryTreeNode currentNode = root;

			// boolean variable to determine if the node has been inserted
			boolean inserted = false;

			// while the node hasn't been inserted
			while (!inserted) {

				// create a position that references the position from current node
				Position currentPos = currentNode.getElement().getPosition();

				// if the position to be inserted is greater than the current position
				if (insertPos.compareTo(currentPos) == 1) {

					// if the right child of the current node is null
					if (currentNode.getRight() == null) {

						/// set the node to be inserted as the right child
						currentNode.setRight(insertNode);

						// set the inserted node's parent to be the current node
						insertNode.setParent(currentNode);

						// set boolean to true to signify that node has been inserted
						inserted = true;
					} 

					// else if the current node has a right child
					else {

						// set the current node to be the right child
						currentNode = currentNode.getRight();
					}
				}

				// else if the current position is greater
				else {

					// if the left child of the current node is null
					if (currentNode.getLeft() == null) {

						// set the node to be inserted as the left child
						currentNode.setLeft(insertNode);

						// set the parent of the inserted node to be the current node
						insertNode.setParent(currentNode);

						// set boolean to true to signify that node has been inserted
						inserted = true;
					} 

					// else if the left child of the current node isn't null
					else {

						// set the current node to be the left child
						currentNode = currentNode.getLeft();
					}
				}
			}
		}

		// increment the number of elements in the tree
		numElem++;
	}

	/**
	 * remove method that removes a node based on a user specified key, calls
	 * upon helper methods to remove the node
	 * @param key The key to be removed
	 */
	public void remove(Position key) throws BSTException {
		// create a node that references an element in the tree that contains the root and key
		BinaryTreeNode nodeRemove = search(this.root, key);

		// if the search returned null
		if(nodeRemove == null){

			// throw an exception
			throw new BSTException("ERROR 404: Node does not exist");
		} 

		else {

			// if the node to be removed is the root
			if(nodeRemove.equals(root)){

				// call helper method removeRoot to remove the node
				removeRoot(nodeRemove);
			} 


			else {

				// call helper method removeNode to remove the node
				removeNode(nodeRemove);
			}

			// decrement the number of elements in the tree
			numElem--;
		}	
	}

	/**
	 * Helper method that removes the root of a Binary Search Tree without
	 * destroying the tree itself
	 * @param node The node to be removed
	 */
	private void removeRoot(BinaryTreeNode node){

		// if the node is a leaf
		if(isLeaf(node)){	

			// set the node to null and the root to null
			node = null;
			this.root = null;
		} 

		// else if the node is the root of binary search tree that is not proper
		else if(oneLeaf(node)){

			// if the node doesn't have a child
			if(node.getLeft() == null){

				// set the root to the right child of the node
				this.root = node.getRight();

				// set the parent of the right child to null
				node.getRight().setParent(null);

				// set the node itself to null
				node = null;
			} 

			else {

				// set the root to the left child of the node
				this.root = node.getLeft();

				// set the parent of the left child to null
				node.getLeft().setParent(null);

				// set the node itself to null
				node = null;
			}
		} 

		// if the tree is proper binary and the root is not a leaf
		else {

			// create a node that references the smallest node on the right side
			BinaryTreeNode smallestRNode = smallestAssistant(node.getRight());

			// set the root to the right child of the node to be removed
			this.root = node.getRight();

			// set the parent of the left child to the smallest node on the right side
			node.getLeft().setParent(smallestRNode);

			// set the left child of the smallest right node to the left child of the node to be removed
			smallestRNode.setLeft(node.getLeft());

			// set the node itself to null
			node = null;
		}
	}

	/**
	 * Helper method that removes an internal node from a proper binary
	 * search tree without destroying the tree
	 * @param node The node to be removed
	 */
	private void removeNode(BinaryTreeNode node){

		// boolean variable that is true if the node is the left child
		boolean isLeftNode = node.getParent().getLeft().equals(node);

		// parent node referencing the parent of the node
		BinaryTreeNode parent = node.getParent();

		// if the node is a leaf
		if(isLeaf(node)){

			// if the node is the left child
			if(isLeftNode){

				// set the left child of the parent to null
				parent.setLeft(null);
			} 

			else {

				// else set the right child of the parent to null
				parent.setRight(null);
			}

			// set the node itself to null
			node = null;
		} 

		// else if the node only has one child
		else if(oneLeaf(node)){

			// if the left child is null
			if(node.getLeft() == null){

				// if the node is the right child
				if(!isLeftNode){

					// set the right child of the parent to the left child of the node
					parent.setRight(node.getLeft());
				} 

				else {

					// else set the left child of the parent to the left child fo the node
					parent.setLeft(node.getLeft());
				}		

				// set the left childs parent as the parent of the node
				node.getLeft().setParent(parent);

				// set the node itself to null
				node = null;
			} 

			else {

				// if the node is the right child
				if(!isLeftNode){

					// set the right child of the parent to the right child of the node
					parent.setRight(node.getRight());
				} 

				else {

					// set the left child of the parent to the right child of the node
					parent.setLeft(node.getRight());
				}

				// set the right childs parent to the parent of the node to be removed
				node.getRight().setParent(parent);

				// set the node itself to null
				node = null;			
			} 	
		}

		// else if the node has two children
		else {

			// create a reference to the smallest node on the right side
			BinaryTreeNode smallestRNode = smallestAssistant(node.getRight());

			// if the node is the right child
			if(!isLeftNode){

				// set the right chilf of the parent to the right child of the node
				parent.setRight(node.getRight());
			} 

			else{

				// set the parents left child to the right child of the node
				parent.setLeft(node.getRight());
			}

			// set the parent of the right child to the parent of the node
			node.getRight().setParent(parent);

			// set the parent of the left child to the smallest node on the right side
			node.getLeft().setParent(smallestRNode);

			// set the left child of the smallest node on the right side to the left child
			smallestRNode.setLeft(node.getLeft());

			// set the node itself to null
			node = null;
		}
	}

	/**
	 * Boolean method that returns true if the node is a leaf
	 * @param node The node to be tested
	 * @return true if node is a leaf; false otherwise
	 */
	private boolean isLeaf(BinaryTreeNode node){
		if(node.getLeft() == null && node.getRight() == null){
			return true;
		}
		else{
			return false;
		}
	}

	/**
	 * Boolean method that returns true if one of the nodes
	 * children is a leaf
	 * @param node The node to be tested
	 * @return true if the node has 1 child; false otherwise
	 */
	private boolean oneLeaf(BinaryTreeNode node){
		if((node.getLeft() != null  && node.getRight() == null) 
				|| (node.getRight() != null && node.getLeft() == null)){
			return true;
		}
		return false;
	}

	/**
	 * Successor method that gets finds the successor of a specified
	 * node with help from helper methods
	 * @param key The key which we are looking for its successor
	 */
	public DictEntry successor(Position key) {

		// if the root is a leaf return null
		if(isLeaf(root)){
			return null;
		}

		// create a successor node that references an element with the key
		BinaryTreeNode successorNode = search(root, key);

		// if the right child is not null
		if(successorNode.getRight() != null){
			// return the result from helper smallestAssistant called on the right child
			return smallestAssistant(successorNode.getRight()).getElement();
		} 

		else {

			// create a parent node that references to the parent of successor node
			BinaryTreeNode parent = successorNode.getParent();

			/*
			 * while the root is not equal to the successor node and 
			 * the right child of the parent is not null and
			 * the right child of the parent is equal to the successor node
			 */
			while(!root.equals(successorNode)  && parent.getRight() != null 
					&& parent.getRight().equals(successorNode)){

				// set the successor node to reference its parent
				successorNode = successorNode.getParent();

				// set the parent to reference the new parent of the successor node
				parent = successorNode.getParent();
			}

			// if the root is equal to the successor node
			if(root.equals(successorNode)){

				// return null
				return null;
			} 

			else {

				// set the successor node to reference its parent
				successorNode = successorNode.getParent();

				// return the element of the successor node
				return successorNode.getElement();
			}
		}
	}

	/**
	 * Predecessor method that finds the predecessor of a specified key
	 * @param key The key which we are looking for its predecessor
	 */
	public DictEntry predecessor(Position key) {

		// create a predecessor node that equals the node with the key
		BinaryTreeNode predecessorNode = search(root, key);

		// if the left child of the predecessor node is null
		if(predecessorNode.getLeft() != null){

			// return the result of the helper method largestAssistant called on the left child
			return largestAssistant(predecessorNode.getLeft()).getElement();
		} 

		else {

			// if the root equals the predecessor node
			if(root.equals(predecessorNode)){

				// return null
				return null;
			} 

			// create a parent that references the parent node of the predecessor node
			BinaryTreeNode parent = predecessorNode.getParent();

			/*
			 * while the root is not equal to the predecessor node and
			 * the left child of the parent is not null and
			 * the left child of the parent is equal to the predecessor node
			 */
			while(!root.equals(predecessorNode)  && parent.getLeft() != null 
					&& parent.getLeft().equals(predecessorNode)){

				// set the predecessor node to reference its parent
				predecessorNode = predecessorNode.getParent();

				// set the parent node to reference the new parent of the predecessor node
				parent = predecessorNode.getParent();
			}

			// if the root equals the predecessor node
			if(root.equals(predecessorNode)){

				// return null
				return null;
			} 

			else {

				// set the predecessor node to its parent
				predecessorNode = predecessorNode.getParent();

				// return the element of the predecessor node
				return predecessorNode.getElement();
			}
		}
	}

	/**
	 * Smallest method that calls a helper method find the smallest node in the tree
	 */
	public DictEntry smallest() {
		return smallestAssistant(this.root).getElement();
	}

	/**
	 * Helper method that finds the smallest node in the tree
	 * @param root The root of the tree
	 * @return null if the root is null; the smallest node otherwise
	 */
	private BinaryTreeNode smallestAssistant(BinaryTreeNode root){

		// if the root is null return null
		if(root == null){
			return null;
		} 

		else {

			// create a node that references the root
			BinaryTreeNode smallestNode = root;

			// while the node has a left child
			while(smallestNode.getLeft() != null){

				// set the node to reference its left child
				smallestNode = smallestNode.getLeft();
			}

			// return the smallest node
			return smallestNode;
		}
	}

	/**
	 * Largest method that calls upon a helper method to return 
	 * the largest node of the tree
	 */
	public DictEntry largest() {
		return largestAssistant(this.root).getElement();
	}

	/**
	 * Helper method that returns the largest node in the tree
	 * @param root The root of the tree
	 * @return null if the root is null; largest node in the tree otherwise
	 */
	private BinaryTreeNode largestAssistant(BinaryTreeNode root){

		// if the root is null return null
		if(root == null){
			return null;
		} 

		else {

			// create a node that references the root
			BinaryTreeNode largestNode = root;

			// while the node has a right child
			while(largestNode.getRight() != null){

				// set the node to reference its right child
				largestNode = largestNode.getRight();
			}

			// return the largest element
			return largestNode;
		}
	}

	/**
	 * Boolean method that checks if the tree is empty or not
	 * @return true if the root of the tree is null; false otherwise
	 */
	private boolean isEmpty(){
		if(this.root == null){
			return true;
		}
		return false;
	}

}
