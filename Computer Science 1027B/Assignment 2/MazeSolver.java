/**
 * @author Jameel Kaba
 * CS1027B Assignment 2
 * The Maze Solver class creates a maze of hexagons
 * and then solves it
 * The Maze Solver will automatically end if an exception is found
 * or if the Solver finds the end hexagon
 * If the end is found it will print out the results in the console
 * showing how many steps it took and how many tiles were left on the stack
 */


import java.io.*;


public class MazeSolver{

	public static void main(String[] args){

		//This class is in a try-catch-finally form

		/**
		 * Try block
		 * This portion of code tries to solve the maze
		 * If any exceptions are found it will be sent to the Catch portion
		 * Where it will display a message and terminate the program
		 */

		try{

			// Checks the args array to find a maze file 
			if(args.length<1){
				throw new IllegalArgumentException("Please provide a Maze file as a command line argument");
			}

			// Creates the maze file based on what was found in the args array
			String mazeFileName = args[0];

			// Create the maze based off of the maze File Name
			Maze maze = new Maze(mazeFileName);

			// Create a hexagon referencing the start tile of the maze
			Hexagon hex = maze.getStart();

			// Create an array stack of type hexagon 
			ArrayStack<Hexagon> stack = new ArrayStack<Hexagon>();

			// Push the hexagon into the stack and set it show as pushed
			stack.push(hex);
			hex.setPushed();

			// Repaint the maze to show the change in hexagon status
			maze.repaint();

			// Create a boolean flag to signify whether or not the end was found
			// As well as create a counter to count the amount of steps it takes
			boolean flag = false;
			int ct = 0;

			// While the stack is not empty and the flag is false
			while(!stack.isEmpty() && flag != true){

				// Increment the counter and pop the stack
				ct++;
				hex = stack.pop();

				// If the hexagon that was popped is the end
				if(hex.isEnd()){

					// Set the flag to true and set the hexagon to processed
					flag = true;
					hex.setProcessed();
				}

				// Else if the hexagon isn't the end
				else{

					// Use a for loop to get the hexagon's neighbors
					for(int i = 0; i < 6; i++){

						// Create a new hexagon that references the original hexagon's neighbors
						Hexagon neighbor = hex.getNeighbour(i);

						// If the hexagon neighbor is not null and is unvisited
						if(neighbor != null && neighbor.isUnvisited()){

							// Push the hexagon neighbor into the stack
							stack.push(neighbor);

							// Set the neighbor as pushed
							neighbor.setPushed();

							// Repaint the maze
							maze.repaint();

						}

						// Set the hexagon to processed
						hex.setProcessed();

					}
				}
			}

			// If the flag is true / the end was found
			if (flag = true){

				// Print out the results showing that the end was found, 
				// how many steps it took, and how many tiles were left on the stack

				System.out.println("The end was found" + "\nIt took " + ct + " steps " 
						+ "\nThere were still " + stack.size() + " tiles left on the stack");
			}

			// If the end was never found
			else{

				// Print out the results showing that the end wasn't found, 
				// how many steps it searched, and if there were any tiles left on the stack

				System.out.println("The end was not found. You are stuck here forever " +
						"\nYou searched " + ct + " steps " + "\nThere were still " + 
						stack.size() + " tiles left on the stack");

			}

		}

		/**
		 * Catch Section
		 * The following code below catches any exceptions that may occur during runtime
		 * And then provides the user with an appropriate error message
		 */

		// Catches File Not Found Exception
		catch (FileNotFoundException e){

			// Prints out an error message
			System.out.println("Caught FileNotFoundException: " + e.getMessage());

		}

		// Catches an IO Exception
		catch (IOException e){

			System.out.println("Caught IOException: " + e.getMessage());

		}

		// Catches an Unknown Maze Character Exception
		catch (UnknownMazeCharacterException e){

			System.out.println("Caught UnknownMazeCharacterException: " + e.getMessage());

		}

		// Catches an Invalid Neighbor Exception
		catch (InvalidNeighborIndexException e) {

			System.out.println("Caught InvalidneighborIndexException: " + e.getMessage());

		}

		// Catches an Empty Collection Exception
		catch (EmptyCollectionException e) {

			System.out.println("Caught EmptyCollectionException: " + e.getMessage());

		}

		// Catches an Array Index Out of Bounds Exception
		catch (ArrayIndexOutOfBoundsException e){

			System.out.println("Caught ArrayIndexOutOfBoundsException: " + e.getMessage());

		}

		// Catches a Null Pointer Exception
		catch (NullPointerException e){

			System.out.println("Caught NullPointerException: " + e.getMessage());

		}

		// Catches an Illegal Argument Exception
		catch (IllegalArgumentException e){

			System.out.println("Caught IllegalArgumentException: " + e.getMessage());

		}

		/**
		 * Finally block
		 * Closes out the program
		 * by thanking the user
		 */

		finally{

			// Prints out a thank you message to the player for playing
			System.out.println("Thank you for playing");

		}
	}
}