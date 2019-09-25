/**
 * LinkedBinaryTree implements the BinaryTreeADT interface
 * 
 * @author Dr. Lewis
 * @author Dr. Chase
 * @version 1.0, 8/19/08
 */

/**
 * @author Jameel Kaba
 * CS1027B Assignment 4
 * This class implements the BinaryTreeADT interface
 * methods added for the assignment are
 * pathToRoot, pathToRootAgain, and lowestCommonAncestor
 */

import java.util.Iterator;

public class LinkedBinaryTree<T> implements BinaryTreeADT<T>
{
	protected int count;
	protected BinaryTreeNode<T> root; 

	/**
	 * Creates an empty binary tree.
	 */
	public LinkedBinaryTree() 
	{
		count = 0;
		root = null;
	}

	/**
	 * Creates a binary tree with the specified element as its root.
	 *
	 * @param element  the element that will become the root of the new binary
	 *                 tree
	 */
	public LinkedBinaryTree (T element) 
	{
		count = 1;
		root = new BinaryTreeNode<T> (element);
	}

	/**
	 * Creates a binary tree with the specified element as its root.
	 *
	 * @param element  the element that will become the root of the new binary
	 *                 tree
	 */
	/**
	 * Constructor creates tree from element as root and two subtrees
	 * as left and right subtrees of root.
	 * @param element		element at root	
	 * @param leftSubtree	left subtree
	 * @param rightSubtree	right subtree
	 */

	public LinkedBinaryTree (T element, LinkedBinaryTree<T> leftSubtree,
			LinkedBinaryTree<T> rightSubtree) 
	{
		root = new BinaryTreeNode<T> (element);
		count = 1;
		if (leftSubtree != null)
		{
			count = count + leftSubtree.size();
			root.left = leftSubtree.root;
		}
		else
			root.left = null;

		if (rightSubtree !=null)
		{
			count = count + rightSubtree.size(); 
			root.right = rightSubtree.root;
		}
		else
			root.right = null;

	}

	/**
	 * Returns a reference to the element at the root
	 *
	 * @return                           a reference to the specified target
	 * @throws EmptyCollectionException  if the tree is empty
	 */
	public T getRoot() throws EmptyCollectionException
	{
		return root.element;
	}

	/**
	 * Returns true if this binary tree is empty and false otherwise.
	 *
	 * @return  true if this binary tree is empty
	 */
	public boolean isEmpty() 
	{
		return count==0; 
	}

	/**
	 * Returns the integer size of this tree.
	 *
	 * @return  the integer size of this tree
	 */
	public int size() 
	{
		return count;
	}

	/**
	 * Returns true if this tree contains an element that matches the
	 * specified target element and false otherwise.
	 *
	 * @param targetElement              the element being sought in this tree
	 * @return                           true if the element in is this tree
	 * @throws ElementNotFoundException  if an element not found exception occurs
	 */
	public boolean contains (T targetElement) 
	{
		return targetElement.equals(find(targetElement));
	}

	/**
	 * Returns a reference to the specified target element if it is
	 * found in this binary tree.  Throws a NoSuchElementException if
	 * the specified target element is not found in the binary tree.
	 *
	 * @param targetElement              the element being sought in this tree
	 * @return                           a reference to the specified target
	 * @throws ElementNotFoundException  if an element not found exception occurs
	 */
	public T find(T targetElement) throws ElementNotFoundException
	{
		BinaryTreeNode<T> current = findAgain( targetElement, root );

		if( current == null )
			throw new ElementNotFoundException("binary tree");

		return (current.element);
	}

	/**
	 * Returns a reference to the specified target element if it is
	 * found in this binary tree.
	 *
	 * @param targetElement  the element being sought in this tree
	 * @param next           the element to begin searching from
	 */
	private BinaryTreeNode<T> findAgain(T targetElement, 
			BinaryTreeNode<T> next)
			{
		if (next == null)
			return null;

		if (next.element.equals(targetElement))
			return next;

		BinaryTreeNode<T> temp = findAgain(targetElement, next.left);

		if (temp == null)
			temp = findAgain(targetElement, next.right);

		return temp;
			}

	/**
	 * Returns a string representation of this binary tree.
	 *
	 * @return  a string representation of this binary tree
	 */
	public String toString() 
	{
		StringBuilder toReturn = new StringBuilder(""); // String toReturn = ""

		Iterator<T> it = this.iteratorInOrder();
		while (it.hasNext()){
			toReturn.append(it.next());  /// += it.next()
		}
		return toReturn.toString(); // return toReturn
	}

	/**
	 * Performs an inorder traversal on this binary tree by calling an
	 * overloaded, recursive inorder method that starts with
	 * the root.
	 *
	 * @return  an in order iterator over this binary tree
	 */
	public Iterator<T> iteratorInOrder()
	{
		ArrayUnorderedList<T> tempList = new ArrayUnorderedList<T>();
		inorder (root, tempList);

		return tempList.iterator();
	}

	/**
	 * Performs a recursive inorder traversal.
	 *
	 * @param node      the node to be used as the root for this traversal
	 * @param tempList  the temporary list for use in this traversal
	 */
	protected void inorder (BinaryTreeNode<T> node, 
			ArrayUnorderedList<T> tempList) 
	{
		if (node != null)
		{
			inorder (node.left, tempList);
			tempList.addToRear(node.element);
			inorder (node.right, tempList);
		}
	}

	/**
	 * Performs an preorder traversal on this binary tree by calling 
	 * an overloaded, recursive preorder method that starts with
	 * the root.
	 *
	 * @return  an pre order iterator over this tree
	 */
	public Iterator<T> iteratorPreOrder() 
	{
		//left as programming project

		// Create an unordered list of generic type T
		ArrayUnorderedList<T> tempList = new ArrayUnorderedList<T>();

		// use the preorder method
		preorder(root, tempList);

		// return the tempList iterator
		return tempList.iterator();
	}

	/**
	 * Performs a recursive preorder traversal.
	 *
	 * @param node  the node to be used as the root for this traversal
	 * @param tempList  the temporary list for use in this traversal
	 */
	protected void preorder (BinaryTreeNode<T> node, 
			ArrayUnorderedList<T> tempList) 
	{
		//if the node does not equal null
		if (node != null){

			// add the node to the rear of the list
			tempList.addToRear(node.getElement());

			// use the preorder method to check 
			// the left and right children
			preorder(node.left, tempList);
			preorder(node.right, tempList);
		}
	}

	/**
	 * Performs an postorder traversal on this binary tree by calling
	 * an overloaded, recursive postorder method that starts
	 * with the root.
	 *
	 * @return  a post order iterator over this tree
	 */
	public Iterator<T> iteratorPostOrder() 
	{
		//left as programming project 
		ArrayUnorderedList<T> tempList = new ArrayUnorderedList<T>();
		postorder(root, tempList);
		return tempList.iterator();
	}

	/**
	 * Performs a recursive postorder traversal.
	 *
	 * @param node      the node to be used as the root for this traversal
	 * @param tempList  the temporary list for use in this traversal
	 */
	protected void postorder (BinaryTreeNode<T> node, 
			ArrayUnorderedList<T> tempList) 
	{
		//if the node is not null
		if (node != null){

			// use the preorder method to check
			// the left and right children 
			preorder(node.left, tempList);
			preorder(node.right, tempList);

			// add the node to the rear of the list
			tempList.addToRear(node.getElement());
		}
	}

	/**
	 * Performs a levelorder traversal on this binary tree, using a
	 * templist.
	 *
	 * @return  a levelorder iterator over this binary tree
	 */
	public Iterator<T> iteratorLevelOrder() 
	{
		// create a new unordered list of type binary tree node
		ArrayUnorderedList<BinaryTreeNode<T>> nodes = new ArrayUnorderedList<BinaryTreeNode<T>>();

		// create a new unordered list of type T
		ArrayUnorderedList<T> result = new ArrayUnorderedList<T>();

		// create a BinaryTreeNode called current
		BinaryTreeNode<T> current;

		// add the root to the rear of the list "nodes"
		nodes.addToRear (root);

		// while the list "nodes" is not empty
		while (! nodes.isEmpty()) 
		{
			// set current equal to the first element of the list "nodes"
			current = (BinaryTreeNode<T>)nodes.removeFirst();

			// if current does not equal null
			if (current != null) 
			{
				// add the current element to the rear of the list "result"
				result.addToRear(current.getElement());

				// add the left and right child to the list "nodes"
				nodes.addToRear (current.left);
				nodes.addToRear (current.right);
			}

			// else add null to the rear of the list "result"
			else
				result.addToRear(null);
		}
		// return the iterator of the list "result"
		return result.iterator();
	}  


	/*************************    Assignment 4    ****************************************/

	/**
	 * @author Jameel Kaba
	 * CS1027B Assignment 4
	 * 
	 * pathToRoot returns a path from an element to the root
	 * pathToRootAgain adds to the path if the node is on the path
	 * lowestCommonAncestor finds the lowest common node between two target elements 
	 */

	/**
	 * Finds the target elements and returns a path from the targetElement to the root. 
	 * It calls a recursive method to do this.
	 * 
	 * @param targetElement
	 * @return Iterator which will iterate over elements on the path from the targetElement 
	 * to the root of the tree (includes both).
	 */

	public Iterator<T> pathToRoot(T targetElement) throws ElementNotFoundException{
		// Create a new unordered list of generic type T

		ArrayUnorderedList<T> pathToRoot = new ArrayUnorderedList<T>();

		// Use the recursive method pathToRootAgain taking variables 
		// targetElement (the element to be found)
		// root (the root of the tree)
		// pathToRoot (the unordered list we created at the start

		pathToRootAgain(targetElement, root, pathToRoot);

		// If the unordered list is empty

		if (pathToRoot.isEmpty() == true){

			// Throw a new Element Not found Exception

			throw new ElementNotFoundException("Binary Tree");
		}

		// Returns the list after being iterated

		return pathToRoot.iterator();

	}

	/**
	 * Will add to the pathToRoot ArrayUnorderedList<T> visitor if the node 
	 * is on the path from the targetElement to the root of the tree
	 * 
	 * @param targetElement
	 * @param node
	 * @param pathToRoot
	 */

	protected void pathToRootAgain(T targetElement, BinaryTreeNode<T> node, ArrayUnorderedList<T> pathToRoot){

		// If the node is not null

		if (node != null){

			// If the node is equal to the target element

			if (node.element.equals(targetElement)){

				// Add the node to the rear of the list

				pathToRoot.addToRear(node.element);

			}

			else{

				// Check the left child using the recursive method

				pathToRootAgain(targetElement, node.left, pathToRoot);

				// If the unordered list is empty

				if (pathToRoot.isEmpty()){

					// Check the right child using the recursive method

					pathToRootAgain(targetElement, node.right, pathToRoot);

				}

				// If the unordered list is not empty

				if (!pathToRoot.isEmpty()){

					// Add the node to the rear of the list

					pathToRoot.addToRear(node.element);

				}
			}
		}
	}

	/**
	 * Finds the lowest (ie. deepest) or maximal-level node common to both the path from 
	 * targetOne to the root and the path from targetTwo to the root.
	 * @param targetOne The first element to find
	 * @param targetTwo The second element to find
	 * @return the element found in the lowest common ancestor node for targetOne and targetTwo
	 * @throws ElementNotFoundException
	 */

	public T lowestCommonAncestor( T targetOne, T targetTwo) throws ElementNotFoundException{

		// Create two iterators that refer to the
		// Path to root for two elements in a tree
		// These may throw the ElementNotFoundException

		Iterator<T> one = pathToRoot(targetOne);

		Iterator<T> two = pathToRoot(targetTwo);

		// Create a new unordered list of generic type T

		ArrayUnorderedList<T> onPathOne = new ArrayUnorderedList<T>();

		// While iterator one has more elements

		while(one.hasNext()){

			// Add the next element from iterator one to the 
			// Rear of the unordered list

			onPathOne.addToRear(one.next());

		}

		// While the second iterator has more elements

		while(two.hasNext()){

			// Create a generic element temp that 
			// Refers to the next element from iterator two

			T temp = two.next();

			// If the unordered list contains temp

			if(onPathOne.contains(temp)){

				// Return the temp element

				return temp;

			}
		}

		// In the worst case scenario 
		// Return the element at the root of the tree

		return root.element;

	}
}
