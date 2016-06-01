/**
 * @author Jameel Kaba
 * CS1027B Assignment 4
 * This class creates a Tree from a file and then lists
 * The path from every element in the tree to the root
 * For example from element D the path to root is D B A
 */
import java.io.*;
import java.util.Iterator;

public class TestPathToRoot {

	public static void main(String[] args) {

		// Create a Linked binary tree of type String and set it to null

		LinkedBinaryTree<String> linkedBinaryTree = null;

		// Create a TreeBuilder of type String and set it to null

		TreeBuilder<String> theTreeBuilder = null;

		/**
		 * Try block
		 * This section tries to create a tree from the file 
		 * Located in args [0]
		 */

		try{

			// Set the tree builder to the file in args[0]

			theTreeBuilder = new TreeBuilder<String>(args[0]);

			// Create the Linked binary tree from the tree builder

			linkedBinaryTree = theTreeBuilder.buildTree();

		}

		/**
		 * Catch block
		 * Catches any possible exceptions that may occur when 
		 * Building the tree
		 */

		// Catch a MalformedTreeFileException 

		catch(MalformedTreeFileException e) {

			// Print out an error message

			System.out.println("MalformedTreeFileException caught: " +  e.getMessage());

		}

		// Catch an IOException

		catch(IOException e){

			// Print out an error message

			System.out.println("Error reading file: " + args[0] + "\n" + e.getMessage());

		}

		// Catch an ElementNotFoundException

		catch(ElementNotFoundException e){

			// Print out an error message

			System.out.println("ElementNotfoundException: " + e.getMessage());

		}

		// Catch any other Exceptions

		catch(Exception e){

			// Print out an error message

			System.out.println("Exception caught: " + e.getMessage());

		}

		/**
		 * Finally block
		 * Once the tree is built the path to root is found for 
		 * All of the elements in the tree and is
		 * Printed out in the console
		 * Or if an Exception is caught 
		 * Tries to find the path to root 
		 */

		finally{

			// Tries to find the path to root 
			try{

				// Create an Iterator of Strings that refers to the 
				// Elements in the tree after it has been iterated by the inorder method

				Iterator<String> treeElements = linkedBinaryTree.iteratorInOrder();

				// Create a String called current

				String current;

				// While the Iterator "treeElements" has more elements

				while(treeElements.hasNext()){

					try{

						// Set current to the next element in the iterator

						current = treeElements.next();

						// Create a new Iterator of Strings called "pathFromCurrent"
						// That refers to the Path to Root for the current element

						Iterator<String> pathFromCurrent = linkedBinaryTree.pathToRoot(current);

						// Print out a message for the current element what it's path to the root is

						System.out.print("For element " + current + " - " + "The path to the root is: ");

						// While "pathFromCurrent" has more elements

						while(pathFromCurrent.hasNext()){

							// Print out the next element from the iterator
							// This adds on to the message printed out earlier

							System.out.print(pathFromCurrent.next() + " ");

						}

						// Print out a blank line so that the messages are not 
						// On one line but on separate lines

						System.out.println();
					}

					// Catches an ElementNotFoundException

					catch(ElementNotFoundException e){

						// Prints out an error message

						System.out.println("ElementNotFoundException caught: " + e.getMessage() 
								+ " Program will try to go throught other elements");

					}
				}
			}

			// Catches a NullPointerException

			catch(NullPointerException e){

				// Prints out an error message

				System.out.println("NullPointerException caught: Please try again");

			}

			// Catches any other exception

			catch(Exception e){

				// Prints out an error message

				System.out.println("Exception caught: " + e.getMessage());

			}
		}
	}

}



