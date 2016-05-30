package ca.uwo.csd.cs2212.team18;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.LinkedList;

/**
 * Class that stores the list of user's created daily goals
 * @author Team 18
 *
 */
public class GoalList implements Serializable{

	/**
	 * Serial version needed for Serializing data
	 */
	private static final long serialVersionUID = 2816988044691305321L;

	/**
	 * The list that stores many lists of goals
	 */
	private ArrayList<LinkedList<Goal>> bigList = new ArrayList<LinkedList<Goal>>(); 

	/**
	 * Constructor method that creates 10000 instances of empty 
	 * linked lists of type goal and stores them into the array list
	 */
	public GoalList(){

		// Create 10000 empty linked lists of type goal
		for(int i = 0; i < 10000; i++){

			// Create an empty linked list of type goal
			LinkedList<Goal> smallList = new LinkedList<Goal>(); 

			// Add the new empty list into position i of the big list
			bigList.add(i, smallList);
		}
	}

	/**
	 * Add method that adds a goal by determining whether or not 
	 * the goal already exists on that date, or if it belongs to a 
	 * list of goals for a specified date
	 * @param goal The goal to be added
	 * @return "" If added successfully; error message otherwise
	 */
	public String add(Goal goal){

		// If the list is empty add the goal
		if(this.bigList.get(0).isEmpty()){
			this.bigList.get(0).add(goal);
			return "";
		}

		else{
			int i = 0;
			// If the list of goals at position i is not empty
			while(!this.bigList.get(i).isEmpty()){

				// Check the date to see if they match
				if(this.bigList.get(i).getFirst().getYear().equals(goal.getYear())){
					if(this.bigList.get(i).getFirst().getMonth().equals(goal.getMonth())){
						if(this.bigList.get(i).getFirst().getDay().equals(goal.getDay())){

							// If date matches then we found the correct list
							for(int j = 0; j < this.bigList.get(i).size(); j++){

								// Check the list of goals for that day to see if that type of goal already exists
								if(this.bigList.get(i).get(j).getType().equals(goal.getType())){

									// Return an appropriate error message as the goal already exists
									return "ERROR: Goal exists please choose a new goal";
								}

							}

							// add the goal to the list of goals for that date
							this.bigList.get(i).add(goal);
							return "";
						}
					}
				}
				// increment i as the list for that date was not found
				i++;
			}
			// Add the goal to the list
			this.bigList.get(i).add(goal);
		}
		return "";
	}

	/**
	 * Remove method that deletes a goal from the big list, only if the goal exists
	 * @param type The type of goal to be removed
	 * @param year The year the goal belongs to
	 * @param month The month the goal belongs to
	 * @param day The day the goal belongs to
	 * @return "" if removed successfully; error message otherwise
	 */
	public String remove(String type, String year, String month, String day){

		// If the list is empty return an error
		if(this.bigList.get(0).isEmpty()){
			return "Error: You don't have any goals";
		}

		else{
			int count = 0;
			// while the list of goals at position count is not empty
			while(!this.bigList.get(count).isEmpty()){

				// Check to see if the dates match
				if(this.bigList.get(count).getFirst().getYear().equals(year)){
					if(this.bigList.get(count).getFirst().getMonth().equals(month)){
						if(this.bigList.get(count).getFirst().getDay().equals(day)){

							// Loop through the list to find the goal to be removed
							for(int i = 0; i < this.bigList.get(count).size(); i++){

								// If the types match up, then remove the goal
								if(this.bigList.get(count).get(i).getType().equals(type)){
									this.bigList.get(count).remove(i);									
									return "";
								}
							}
						}
					}
				}
				// Increment the counter
				count++;
			}
			// Return an error message as the goal does not exist on that date
			return "ERROR: There are no goals of this type on this date";
		}
	}

	/**
	 * Valid method, that checks the goal list to see if it meets 
	 * the requirements of 4+ goals needed on a specified date
	 * @param year The year to be checked
	 * @param month The month to be checked 
	 * @param day The day to be checked
	 * @return true if valid; false if not
	 */
	public Boolean valid(String year, String month, String day){
		// If the list is empty then return true, as they haven't added a goal yet
		if(this.bigList.get(0).isEmpty()){
			return true;
		}

		else{
			// Loop through the list to see if there are at least 4 goals
			for(int i = 0; i < this.bigList.size(); i++){
				if(!this.bigList.get(i).isEmpty()){
					int count = 0;
					for(int j = 0; j < this.bigList.get(i).size(); j++){
						count++;
					}
					// if there are 4 or more goals return true
					if(count >= 4){
						return true;
					}
				}
			}
		}
		// return false as there are between 0 and 4 goals
		return false;
	}

	/**
	 * toString method that prints out the contents of the list 
	 * and whether or not it has been met by getting data
	 * @param year The year to be checked
	 * @param month The month to be checked 
	 * @param day The day to be checked
	 * @param dat The data to be used for the checks
	 * @return The contents of the goal list on that specified date
	 */
	public String toString(String year, String month, String day, Data dat){
		// Create an empty string
		String alt = "";

		// if the list is empty then return "" as there are no goals to be displayed
		if(this.bigList.get(0).isEmpty()){
			return "";
		}

		// loop through the list
		for(int i = 0; i < this.bigList.size(); i ++){

			// if the list is empty on the date to be found then exit
			if(this.bigList.get(i).isEmpty()){
				break;
			}

			//Check the dates to see if they match
			if(this.bigList.get(i).getFirst().getYear().equals(year)){
				if(this.bigList.get(i).getFirst().getMonth().equals(month)){
					if(this.bigList.get(i).getFirst().getDay().equals(day)){

						// Loop through the list to get the goals for that date
						for(int j = 0; j < this.bigList.get(i).size(); j++){

							// Add the toString for the goal
							alt = alt.concat(this.bigList.get(i).get(j).toString());

							// Save the type of the goal into a variable for comparison
							String typ = this.bigList.get(i).get(j).getType();

							// If the type is equal to steps
							if(typ.equals("Steps")){

								// Get the value of steps from the data
								int stepC = dat.getSteps().getValue();

								// If the user met the step goal add (complete) to the string
								if(stepC >= this.bigList.get(i).get(j).getMeasure()){
									alt = alt.concat(" (Complete)");
								}

								// If the user has not met the goal then add (incomplete) to the string
								else{
									alt = alt.concat(" (Incomplete)");
								}
							}

							// If the type is equal to distance
							else if(typ.equals("Distance")){

								// Get the value of distance from the data
								int distC  = dat.getDistance().getValue();

								// If the user met their goal for distance add (complete) to the string
								if(distC >= this.bigList.get(i).get(j).getMeasure()){
									alt = alt.concat(" (Complete)");
								}

								// Else add (incomplete) to the string
								else{
									alt = alt.concat(" (Incomplete)");
								}
							}

							// If the type is equal to floors
							else if(typ.equals("Floors")){

								// Get the value of floors climbed from the data
								int floorC = dat.getFloors().getValue();

								// If the user met there goal then add (complete) to the string
								if(floorC >= this.bigList.get(i).get(j).getMeasure()){
									alt = alt.concat(" (Complete)");
								}

								// Else add (incomplete) to the string
								else{
									alt = alt.concat(" (Incomplete)");
								}
							}

							// If the type is equal to Active minutes
							else if(typ.equals("Active minutes")){

								// Get the value for Active minutes from the data
								int actC = dat.getActMin().getValue();

								// See if the user met their goal, if so then add (complete) to the string
								if(actC >= this.bigList.get(i).get(j).getMeasure()){
									alt = alt.concat(" (Complete)");
								}

								// Else add (incomplete) to the string
								else{
									alt = alt.concat(" (Incomplete)");
								}
							}

							// If the type is equal to calories
							else if(typ.equals("Calories")){

								// Get the value for calories from the data
								int calC = dat.getCaloriesOut().getValue();

								// If the user met their goal. then add (complete) to the string
								if(calC >= this.bigList.get(i).get(j).getMeasure()){
									alt = alt.concat(" (Complete)");
								}

								// Else add (incomplete) to the string
								else{
									alt = alt.concat(" (Incomplete)");
								}
							}

							// Add a new line to the string
							alt = alt.concat("\n");
						}
						break;
					}
				}
			}
		}
		// Return the String
		return alt;
	}

	/**
	 * isEmpty method used to determine if the list is empty 
	 * @return true if empty; false otherwise
	 */
	public Boolean isEmpty(){
		// If the first list of goals is empty, return true
		if(this.bigList.get(0).isEmpty()){
			return true;
		}
		// Else return false
		return false;
	}

	/**
	 * Store method that saves the goal list onto a 
	 * file so that it may be reused/loaded for future usage 
	 * @throws Exception if the file is not found / does not exist
	 */
	public void store() throws Exception {
		// Create a file for saving
		ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream("List.dat"));

		// Save the goal list onto the file
		out.writeObject(this);

		// Close the saved file
		out.close();
	}

	/**
	 * Load method that loads a goal list from a file
	 * @return The goal list loaded
	 * @throws Exception If file not found / file does not exist
	 */
	public static GoalList load() throws Exception {

		// Try to open the file for loading
		ObjectInputStream in = new ObjectInputStream(new FileInputStream("List.dat"));

		// Create a goal list based off the loaded file
		GoalList goal = (GoalList) in.readObject();

		// Close the loaded file
		in.close();

		// Return the goal list that was loaded
		return goal;
	}

}
