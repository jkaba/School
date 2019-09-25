package ca.uwo.csd.cs2212.team18;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
/**
 * Handles all the FitCalc backend for both UIs
 * @author Team18
 *
 */
public class FitCalc {
	//Initialize some variables
	private int calorieGoal;
	private int caloriesBurned;
	private int calorieDifference;
	boolean test = true;
	private boolean negativeDifference;
	private int numberOfFitbitActivities;
	private int weightKg;
	private String[][] displayActivities= new String[3][6];
	private String[][] displayDefaultActivities = new String[3][6];
	
	private DateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");

	//get current date time with Date()
	private Date date = new Date();
	private String fulldate = dateFormat.format(date);
	private String curYear = fulldate.substring(0,4);
	private String curMonth = fulldate.substring(4,6);
	private String curDay = fulldate.substring(6,8);

	private String apiInput = "";
	{
		apiInput = apiInput.concat(curYear);
		apiInput = apiInput.concat("-");
		apiInput = apiInput.concat(curMonth);
		apiInput = apiInput.concat("-");
		apiInput = apiInput.concat(curDay);
	}
	
	private Data data;
	
	/**
	 * Constructor for the class
	 * @param datas
	 * @param testOrNot
	 */
	public FitCalc(Data datas, boolean testOrNot) {		
		data = datas;
		
	}
	
	/**
	 * Method that checks if the calorie input is valid
	 * @param input
	 * @return String depending on whether or not input valid
	 */
	public String checkCaloriesInput(String input) {
		//Checks if user has inputed something
		if (input.length() == 0) {
			return "Please type in the textfield a calorie goal";
		}
		//Checks if user has inputed non-numbers
		for ( int i=0;i<input.length(); i++) {
			if ((int)(input.charAt(i)) > 57 || (int)(input.charAt(i)) < 48) {
				return "Please input only numbers into the textfield";
			}
		}
		if (Integer.parseInt(input) > 12000) {
			return "Unless you are an Olympic swimmer like Michael Phelps, burning over 12,000 calories a day is unrealistic. Please input a more appropriate goal.";
		}
		return "";
	}
	/**
	 * Sets the calorie goal into private variable
	 * @param input
	 */
	public void setCalorieGoal(int input) {
		calorieGoal = input;
	}
	
	/**
	 * Sets various String[][] which hold text and label Strings which will appear on the FitCalcUI2
	 * @param testBool
	 * @return String depending on whether or not can successfully get data from fitbit
	 */
	
	public String calculate(boolean testBool) {
		caloriesBurned = data.getCaloriesOut().getValue();
		calorieDifference = calorieGoal - caloriesBurned;
		if (calorieDifference < 0) {
			negativeDifference = true;
		}
		else { negativeDifference = false; }
		
		
		weightKg = 50;
	
		//Initialize the Default Activities array
		displayDefaultActivities[0][0] = "First Activity:     ";
		displayDefaultActivities[0][1] = "Walking";
		displayDefaultActivities[0][2] = "Activity's METS:     ";
		displayDefaultActivities[0][3] = Integer.toString(3);
		displayDefaultActivities[0][4] = "Suggested Time:     ";
		displayDefaultActivities[0][5] = Integer.toString(this.caloriesCalculation(3, weightKg));
		
		displayDefaultActivities[1][0] = "Second Activity:     ";
		displayDefaultActivities[1][1] = "Jogging";
		displayDefaultActivities[1][2] = "Activity's METS:     ";
		displayDefaultActivities[1][3] = Integer.toString(7);
		displayDefaultActivities[1][4] = "Suggested Time:     ";
		displayDefaultActivities[1][5] = Integer.toString(this.caloriesCalculation(7,weightKg));
		
		displayDefaultActivities[2][0] = "Third Activity:     ";
		displayDefaultActivities[2][1] = "Running at 6mins/mile";
		displayDefaultActivities[2][2] = "Activity's METS:     ";
		displayDefaultActivities[2][3] = Integer.toString(14);
		displayDefaultActivities[2][4] = "Suggested Time:     ";
		displayDefaultActivities[2][5] = Integer.toString(this.caloriesCalculation(14,weightKg));
		
		//apiData get the # of activities MAX can only be 3 
				//Initialize the displayActivities array		
		try {
		FitCalcActivity[] array = data.getRecentActivities();
		displayActivities[0][0] = "First Activity:     ";
		displayActivities[0][1] = array[0].getType();
		displayActivities[0][2] = "Activity's METS:     ";
		int a = (int) array[0].getMets();
		displayActivities[0][3] = Integer.toString(a);
		displayActivities[0][4] = "Suggested Time:     ";
		displayActivities[0][5] = Integer.toString(this.caloriesCalculation(a, weightKg));
		
		displayActivities[1][0] = "Second Activity:     ";
		displayActivities[1][1] = array[1].getType();
		displayActivities[1][2] = "Activity's METS:     ";
		int b = (int) array[1].getMets();
		displayActivities[1][3] = Integer.toString(b);
		displayActivities[1][4] = "Suggested Time:     ";
		displayActivities[1][5] = Integer.toString(this.caloriesCalculation(b,weightKg));

		displayActivities[2][0] = "Third Activity:     ";
		displayActivities[2][1] = array[2].getType();
		displayActivities[2][2] = "Activity's METS:     ";
		int c = (int) array[2].getMets();
		displayActivities[2][3] = Integer.toString(c);
		displayActivities[2][4] = "Suggested Time:     ";
		displayActivities[2][5] = Integer.toString(this.caloriesCalculation(c,weightKg));	
		}
		catch (Exception e) {
			return "The app is unable to access fitbit activities";
		}

		return "";	
	}
	
	/**
	 * Calculates the suggestions based off of the METS and weight
	 * @param METS
	 * @param weight
	 * @return The minutes that one should spend doing a specific activity
	 */
	public int caloriesCalculation(int METS, int weight) {
		int multiply = METS * weight;
		double time = (double) calorieDifference/ (double) multiply;
		double minutes = time * (double) 60;
		int realMins = (int) minutes;
		return realMins;
	}
	
	/**
	 * Returns a String[][] based on whether or not in test mode 
	 * @param defaultActivities
	 * @return a String[][] with values for the labels and textfields in FitCalcUI2
	 */
	
	public String[][] getDisplayStrings(boolean defaultActivities) {
		if (defaultActivities == true) {
			return displayDefaultActivities;
		}
		return displayActivities;
	}
	
	//Setters and Getters
	public int getNumberOfFitbitActivities() {
		return numberOfFitbitActivities;
	}
	public boolean getNegativeDifference() {
		return negativeDifference;
	}
	
	public int getCalorieGoal() {
		return calorieGoal;
	}
	public int getCaloriesBurned() {
		return caloriesBurned;
	}
	public int getCalorieDifference() {
		return calorieDifference;
	}
	
	
}
