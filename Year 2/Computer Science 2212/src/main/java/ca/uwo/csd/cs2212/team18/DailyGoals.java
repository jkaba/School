package ca.uwo.csd.cs2212.team18;
import java.awt.List;
import java.io.File;
import java.io.Serializable;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.ObjectInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.util.*;

/**
 * Class that saves, loads, and checks date and measure variables in the daily goals component
 * @author Team 18
 */
public class DailyGoals implements Serializable{

	//private variables

	/**
	 * Integer to represent the year
	 */
	private int year;

	/**
	 * Integer to represent the month
	 */
	private int month;

	/**
	 * Integer to represent the day
	 */
	private int day;

	/**
	 * Constructor method to create an instance of Daily Goals 
	 */
	public DailyGoals(){
	}

	/**
	 * Method used to check user input, when adding a goal
	 * @param input The input to be checked
	 * @return an appropriate error message if the input is not valid; "" if valid
	 */
	public static String checkMeasureInput(String input){

		// If the input is blank/null return an error message
		if(input.length() == 0){
			return "Please input a measurable value";
		}

		else{
			for ( int i=0;i<input.length(); i++) {
				// If the input is a letter(s) / negative number return an error message
				if ((int)(input.charAt(i)) > 57 || (int)(input.charAt(i)) < 48) {
					return "Please input a positive number";
				}
			}
		}
		// Return "" if input is correct
		return "";
	}

	/**
	 * Method to check user input, when changing the date
	 * @param year The year to be checked
	 * @param month The month to be checked
	 * @param day The day to be checked
	 * @return an appropriate error message if the input is not valid; "" if valid
	 */
	public static String checkDateInput(String year, String month, String day) {

		// If year, month, or day are not of the proper length return an error message
		if (year.length() != 4 || month.length() != 2 || day.length() != 2) {
			return "Please input date with 4 numbers in year, 2 numbers in month and 2 numbers in day";
		}

		// Combine the date together in a string
		String combine = "";
		combine = combine.concat(year);
		combine = combine.concat(month);
		combine = combine.concat(day);

		// If the input features a letter, then return an error message
		for ( int i=0;i<combine.length(); i++) {
			if ((int)(combine.charAt(i)) > 57 || (int)(combine.charAt(i)) < 48) {
				return "Please input a number";
			}
		}

		// If the month value is invalid, return an error message
		if (Integer.parseInt(month) > 12 || Integer.parseInt(month) == 00) {
			return "Month value is invalid";
		}

		// If the day value is invalid, return an error message
		if (Integer.parseInt(day) > 31 || Integer.parseInt(day) == 00) {
			return "Day value is invalid";
		}

		// Check whether it is an odd or even month
		int oddOrEvenMonth = Integer.parseInt(month) % 2;
		// Check if the day value is valid
		if (oddOrEvenMonth == 0 && Integer.parseInt(month) < 8 && Integer.parseInt(day) == 31) {
			return "Day value is invalid";
		}

		// Check if the day value is valid
		if (oddOrEvenMonth == 1 && Integer.parseInt(month) > 8 && Integer.parseInt(day) == 31) {
			return "Day value is invalid";
		}

		// If month is February, check to see if the day is valid
		if (Integer.parseInt(month) == 2 && (Integer.parseInt(day) == 30 || Integer.parseInt(day) == 31)) {
			return "Day value is invalid";
		}

		// If it is a leap year, then check to see if the day is valid in February
		int yearDiv = Integer.parseInt(year) % 4;
		if (yearDiv != 0 && Integer.parseInt(day) == 29) {
			return "Day value is invalid";
		}

		// Format the date
		DateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");

		// Build the date
		Date date = new Date();
		String fulldate = dateFormat.format(date);
		String curYear = fulldate.substring(0,4);
		String curMonth = fulldate.substring(4,6);
		String curDay = fulldate.substring(6,8);

		year = curYear;
		month = curMonth;
		day = curDay;

		// Check to see if the year, is valid (Not in the future)
		if (Integer.parseInt(curYear) < Integer.parseInt(year)) {
			return "We can't look at data on a future date... yet. In the meantime input a date in the past";
		}

		// Check to see if the month is valid (Not in the future)
		if (Integer.parseInt(curMonth) < Integer.parseInt(month) && Integer.parseInt(curYear) == Integer.parseInt(year)) {
			return "We can't look at data on a future date... yet. In the meantime input a date in the past";
		}

		// Check to see if the day is valid (Not in the future)
		if (Integer.parseInt(curDay) < Integer.parseInt(day) && Integer.parseInt(curYear) == Integer.parseInt(year) && Integer.parseInt(curMonth) == Integer.parseInt(month)) {
			return "We can't look at data on a future date... yet. In the meantime input a date in the past";
		}

		return "";
	}

	/* Getters and Setters */

	/**
	 * Getter method to get the year 
	 * @return the year
	 */
	public int getYear() {
		return year;
	}

	/**
	 * Setter method to set the year
	 * @param year The new year value
	 */
	public void setYear(int year) {
		this.year = year;
	}

	/**
	 * Getter method to get the month
	 * @return the month
	 */
	public int getMonth() {
		return month;
	}

	/**
	 * Setter method to set the month
	 * @param month The new month value
	 */
	public void setMonth(int month) {
		this.month = month;
	}

	/**
	 * Getter method to get the day
	 * @return the day
	 */
	public int getDay() {
		return day;
	}

	/**
	 * Setter method to set the day 
	 * @param day The new day value
	 */
	public void setDay(int day) {
		this.day = day;
	}

	/**
	 * Load method, that attempts to load a goal list
	 * @return a loaded goal list; a blank goal list otherwise
	 */
	public static GoalList load(){

		// Create a new goal list
		GoalList goal = new GoalList();

		try{
			// Try to load a goal list
			goal = GoalList.load();

			// If load successful, then return the loaded goal list
			return goal;
		}

		catch(Exception e){
			// If the list can't be loaded, then create a blank goal list
			GoalList go = new GoalList();

			// return the blank list
			return go;
		}
	}

	/**
	 * Save method that saves a goal list onto a file
	 * @param goal The goal list to be saved
	 */
	public static void save(GoalList goal){
		try {
			// Try to save the goal list
			goal.store();
		} 
		// Catch the exception if it occurs
		catch (Exception e) {
			e.printStackTrace();
		}
	}

}
