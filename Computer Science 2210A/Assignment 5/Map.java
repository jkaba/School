/**
 * CS2210A Assignment 5
 * @author Jameel Kaba (jkaba) Student #: 250796017
 * 
 * Map class that represents a map of bus lines
 */

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Iterator;
import java.util.Stack;


public class Map{

	// Private variables
	private Graph map;	
	private int changes;	
	private Node start, end;	
	private Stack<Node> stack;	


	/** 
	 * Constructor method that builds a map based on the input file passed through
	 * as a parameter.
	 * @param inputFile The file used to build the map
	 * @throws MapException Thrown if the input file doesn't exist
	 */
	public Map(String inputFile) throws MapException{

		try {

			stack = new Stack<Node>();
			BufferedReader input = new BufferedReader(new FileReader(inputFile));
			String line = input.readLine();

			// Get the width of the map
			line = input.readLine();
			int width = Integer.parseInt(line);

			// Get the length of the map
			line = input.readLine();
			int length = Integer.parseInt(line);

			// Create a graph with number of nodes being the value of width * length
			map = new Graph(width * length);

			// Get the number of bus line changes
			line = input.readLine();
			changes = Integer.parseInt(line);

			// Get the first line of elements
			line = input.readLine();

			// Initialize counters
			int countNode = 0;
			int columnCount = 0;
			int columnNode = 0;
			int counter = 0;

			for(int i = 0; i < (length*2)-1; i++){
				for(int j = 0; j < (width*2)-1; j++){

					// If it is an even row 
					if (i%2 == 0){

						// If it is an even column
						if (j%2 == 0){

							// If the character is a zero set the starting point
							if(line.charAt(j) == '0'){
								start = map.getNode((i/2*width) + (j/2));
							}

							// If the character is a one set the end point
							else if(line.charAt(j) == '1'){
								end = map.getNode((i/2*width) + (j/2));
							}

							// If the character is a + do nothing
							else if(line.charAt(j) == '+'){
							}

							// If the character is a space then increment the node counter
							else if(line.charAt(j) == ' '){
								countNode++;

							}

							// else it is a letter so insert an edge
							else{

								// Create a String for the bus line
								String s = ""; 
								s = s + line.charAt(j);

								/*
								 * insert an edge into the graph with the first endpoint being
								 * the node represented by the counter and the second endpoint
								 * being the node represented by the next node after the first endpoint
								 * and the busline being the string we created.
								 */
								map.insertEdge(map.getNode(countNode), map.getNode(countNode+1), s);

								// increment the node counter
								countNode++;

							}
						}

						// else if the column is odd
						else{

							// If the character is 0 set the starting point
							if(line.charAt(j) == '0'){
								start = map.getNode((i/2*width) + (j/2));
							}

							// If the character is 1 set the end point
							else if(line.charAt(j) == '1'){
								end = map.getNode((i/2*width) + (j/2));
							}

							// If the character is a +  then do nothing
							else if(line.charAt(j) == '+'){
							}

							// If the character is a space increment the node counter
							else if(line.charAt(j) == ' '){
								countNode++;

							}

							// else the character is a letter so insert an edge
							else{

								// Make a string for the bus line
								String s = ""; 
								s = s + line.charAt(j);

								/*
								 * insert an edge into the graph with the first endpoint being
								 * the node represented by the counter and the second endpoint
								 * being the node represented by the next node after the first endpoint
								 * and the busline being the string we created.
								 */
								map.insertEdge(map.getNode(countNode), map.getNode(countNode+1), s);
								countNode++;

							}
						}
					}

					// Else if it's an odd row
					else{

						// If the column is even
						if (j%2 == 0){

							// If the character is a space
							if(line.charAt(j) == ' '){

								// Increment the column node counter
								columnNode++;
								columnCount++;
							}

							// else if the character is a letter insert an edge
							else{

								// Create a string for the busline
								String s = ""; 
								s = s + line.charAt(j);

								/*
								 * insert an edge into the graph with the first endpoint being
								 * the number column counter represented by the counter and the second endpoint
								 * being the node represented by the column node counter 
								 * and the busline being the string we created.
								 */
								map.insertEdge(map.getNode(columnCount), map.getNode(columnNode), s);

								// Increment the column node counter and the column counter
								columnNode++;
								columnCount++;
							}
						}

						//else if the column is odd
						else{

							// if the character is a space
							if(line.charAt(j) == ' '){
							}

							// else the character is a letter
							else{

								// Set a string for the busline
								String s = ""; 
								s = s + line.charAt(j);

								/*
								 * insert an edge into the graph with the first endpoint being
								 * the node represented by the counter and the second endpoint
								 * being the node represented by the next node after the first endpoint
								 * and the busline being the string we created.
								 */
								map.insertEdge(map.getNode(columnCount), map.getNode(columnNode), s);
								columnNode++;
								columnCount++;

							}
						}
					}
				}

				// set line to read the next line of characters
				line = input.readLine();

				// If the counter is even
				if(counter%2==0){

					// Increment the node counter
					countNode++;
				}

				// When the counter is zero
				if(counter==0){

					// Set the column node counter to equal the width
					columnNode = width;
				}

				counter++;
			}
		} 

		// Catch an exception and send a message
		catch (Exception e) {	
			throw new MapException("Problem with input file");
		}
	}


	/**
	 * Getter method that returns the graph representing the map
	 * @return The graph that represents the map
	 * @throws MapException If the graph is not initialized
	 */
	public Graph getGraph() throws MapException{
		if (map != null)
			return map;
		else
			throw new MapException("Graph not initalized");
	}

	/**
	 * Find path method that tries to find the path from the starting
	 * node to the ending node storing the elements in an iterator
	 * @return A stack iterator containing the nodes along the path
	 * from the starting node to the destination
	 * @return null if the path does not exist
	 * @throws GraphException if the graph/map is not proper
	 */
	public Iterator<Node> findPath(){
		try {

			// Create an iterator of the incident edges from start
			Iterator<Edge> incident = map.incidentEdges(start);

			// Create an edge called check used in the helper method
			Edge check = new Edge(start, end, "string");

			// While the iterator is not empty
			while(incident.hasNext()){

				// Set check to be the next element in the iterator
				check = incident.next();

				// Call the helper method to find a path
				path(start, end, check);

				// If the stack is not empty return the iterator
				if(!stack.empty()){
					return stack.iterator();
				}
			}
		} 
		// Catch an exception if the graph is not proper
		catch (GraphException e) {
			System.out.println("Error: Exception caught");
		}

		// returns null if the path does not exist
		return null;
	}

	/**
	 * Helper method used to find the path from a starting node to 
	 * the destination node, storing all the nodes in the path
	 * into a stack or popping them off the stack if the path
	 * does not lead to the end
	 * @param start The starting node
	 * @param end The ending/destination node
	 * @param check The edge used to check buslines
	 * @return true if a path exists, false otherwise
	 */
	private boolean path(Node start, Node end, Edge check){

		// push the starting node into the stack
		stack.push(start);

		// if the start is the end return true
		if(start == end){
			return true;
		}

		else{
			try {

				//set the starting nodes mark to true
				start.setMark(true);

				// Create an iterator that has the nodes incident to start
				Iterator<Edge> incident = map.incidentEdges(start);

				// While the iterator has next
				while(incident.hasNext()){

					// Create a node called discovery that is the next edge on the iterator
					Edge discovery = incident.next();

					// Create a node u that is the second end point of discovery
					Node u = discovery.secondEndpoint();

					// If the mark on node u is false
					if(u.getMark() != true){

						// if discovery edge and check edge have different bus lines
						if(discovery.getBusLine().equals(check.getBusLine())){
							check = discovery;

							// See if there is a path with u being the start
							if(path(u, end, check)){

								// If there is a path return true
								return true;

							
							}
						}

						// else if the bus lines are the same
						else{

							if(changes > 0){

								// decrement the changes
								changes--;

								// set check to reference discovery
								check = discovery;

								// Call path recursively with u being the start
								if(path(u,end,check)){

									// If a path is found return true
									return true;
								}

								// If a path wasn't found increment changes
								changes++;
							}
						}
					}
				}

				// If there isn't a path set the starting nodes mark to false
				start.setMark(false);

				// pop the stack
				stack.pop();
			}	

			// Catch a graph exception if there are invalid edges
			catch (GraphException e) {
				System.out.println("ERROR: Invalid Graph");
			}
		}
		// Return false as there is no path
		return false;
	}

}