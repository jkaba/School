/**
 * @author Jameel Kaba
 * CS1027B Assignment 4
 * This class creates a tree and then finds 
 * The lowest common node between two elements 
 * For example the common element between D and E is B
 */

import java.io.*;

public class FindCommonAncestor {
	public static void main(String[] args){

		// Create a new buffered reader

		BufferedReader consoleReader  = new BufferedReader(new InputStreamReader(System.in));

		// Create a Linked binary tree of type String and set it to null

		LinkedBinaryTree<String> linkedBinaryTree = null;

		// Create a Tree builder of type String and set it to null

		TreeBuilder<String> treeBuilder = null;


		try{

			// Set the tree builder to the file located in args[0]

			treeBuilder = new TreeBuilder<String>(args[0]);

			// Build the linked binary tree from that file

			linkedBinaryTree = treeBuilder.buildTree();

			// Print out the contents of the tree

			System.out.println("The Tree Contains: " + linkedBinaryTree);

			// Prompt the user to enter Two elements to be compared

			System.out.print("Enter first element: ");

			String firstNode = consoleReader.readLine();

			System.out.print("Enter second element: ");

			String secondNode = consoleReader.readLine();


			// Print the lowest common ancestor between the two elements

			System.out.println("The lowest common ancestor is: " + 

					linkedBinaryTree.lowestCommonAncestor(firstNode, secondNode));

		}

		/**
		 * Catch block
		 * The following section are where the exceptions are handled
		 */

		// Catch a MalformedTreeException

		catch(MalformedTreeFileException e) {

			// Print out an error message

			System.out.println("MalformedTreeFileException: " + e.getMessage());

		}

		// Catch an IOException

		catch(IOException e){

			// Print out an error message

			System.out.println("Error reading file: " + args[0] + "\n" + e.getMessage());

		}

		// Catch an ElementNotFoundException

		catch(ElementNotFoundException e){

			// Print out an error message

			System.out.println("ElementNotFoundException caught: " + e.getMessage());

		}

		// Catch any other exception that may occur

		catch(Exception e){

			// Print out an error message

			System.out.println("Exception caught: " + e.getMessage());

		} 

		/**
		 * Finally block
		 * Closes the console reader
		 */

		finally{

			try{

				// Tries to close the consoleReader

				consoleReader.close();

			}

			// Catches an IOException

			catch(IOException e){

				// Prints out an error message

				System.out.println("IOException caught: " + e.getMessage());

			}

			// Catches any other exception possible

			catch(Exception e){

				// Prints out an error message
				System.out.println("Exception Caught: " + e.getMessage());

			}
		}
	}
}

