package ca.uwo.csd.cs2212.team18;
import java.io.Serializable;

/**
 * Class that holds data to be stored in goalList class and displayed onto the UI
 * @author Team 18
 *
 */
public class Goal implements Serializable{

	//Private Variables

	/**
	 * String representing the type of goal
	 */
	private String type;

	/**
	 * Integer representing the measure of the goal
	 */
	private int measure;

	/**
	 * Integer value representing the year of the goal
	 */
	private String year;

	/**
	 * Integer value representing the month of the goal
	 */
	private String month;

	/**
	 * Integer value representing the day of the goal
	 */
	private String day;

	/**
	 * Constructor to make a new Goal 
	 * @param type The type of goal
	 * @param measure The measure for the goal
	 * @param year The year of the goal
	 * @param month The month of the goal
	 * @param day The day of the goal
	 */
	public Goal(String type, int measure, String year, String month, String day){
		this.type = type;
		this.measure = measure;
		this.year = year;
		this.month = month;
		this.day = day;
	}

	/* Getters and Setters */

	/**
	 * Getter method to get the year of the goal 
	 * @return the year of the goal
	 */
	public String getYear() {
		return year;
	}

	/**
	 * Setter method to set the year of a goal
	 * @param year The new year for the goal
	 */
	public void setYear(String year) {
		this.year = year;
	}

	/**
	 * Getter method to get the month of a goal
	 * @return the month of the goal
	 */
	public String getMonth() {
		return month;
	}

	/**
	 * Setter method to set the month of a goal
	 * @param month The new month of the goal
	 */
	public void setMonth(String month) {
		this.month = month;
	}

	/**
	 * Getter method that gets the day for the goal
	 * @return the day of the goal
	 */
	public String getDay() {
		return day;
	}

	/**
	 * Setter method to set the day for the goal
	 * @param day The new day of the goal
	 */
	public void setDay(String day) {
		this.day = day;
	}

	/**
	 * Getter method to get the type of goal
	 * @return the type of goal
	 */
	public String getType() {
		return type;
	}

	/**
	 * Setter method that sets the type of goal
	 * @param type The new type of goal
	 */
	public void setType(String type) {
		this.type = type;
	}

	/**
	 * Getter method that gets the measure of a goal
	 * @return the measure for the goal
	 */
	public int getMeasure() {
		return measure;
	}

	/**
	 * Setter method to set the measure of a goal
	 * @param measure The new measure for the goal
	 */
	public void setMeasure(int measure) {
		this.measure = measure;
	}

	/**
	 * toString method that returns an appropriate String 
	 * based on what type of goal it is
	 * @return an appropriate description based on the type of goal; "" if not applicable
	 */
	public String toString(){

		//Based on the type of goal, return an appropriate description
		if(this.type.equals("Steps")){
			return type + ": walk " + measure + " steps";
		}
		else if(this.type.equals("Floors")){
			return type + ": climb " + measure + " floors";
		}
		else if(this.type.equals("Distance")){
			return type + ": walk " + measure + " km";
		}
		else if(this.type.equals("Calories")){
			return type + ": burn " + measure + " calories";
		}
		else if(this.type.equals("Active minutes")){
			return type + ": stay active for " + measure + " minutes";
		}
		return "";
	}

}