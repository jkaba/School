package ca.uwo.csd.cs2212.team18;

import java.text.SimpleDateFormat;
import java.util.Calendar;

/**
 * Abstract parent class for the APIData and TestData classes
 * that will store all the attributes
 * @author Team 18 
 *
 */
public abstract class Data {

	// Initializes activity variables to store the Activity information
	protected Activity caloriesOut = new Activity("Calories Out");
	protected Activity floors = new Activity("Floors");
	protected Activity steps = new Activity("Steps");
	protected Activity actMin = new Activity("Active Minutes");
	protected Activity sedMin = new Activity("Sedentary Minutes");
	protected Activity distance = new Activity("Distance");
	// Initializes Activity object that stores the resting heart rate
	protected Activity restingHeartRate = new Activity("Resting Heart Rate");
	// Initializes BestActivity objects that will store that best activities
	protected BestActivity bestDistance = new BestActivity("Distance");
	protected BestActivity bestFloors = new BestActivity("Floors");
	protected BestActivity bestSteps = new BestActivity("Steps");
	// Initializes Activity objects that will store the total activities
	protected Activity totalDistance = new Activity("Distance");
	protected Activity totalFloors = new Activity("Floors");
	protected Activity totalSteps = new Activity("Steps");
	// Initializes the HeartRateZone objects that will store the various heart rate zones
	protected HeartRateZone outOfRange = new HeartRateZone("Out of Range");
	protected HeartRateZone fatBurn = new HeartRateZone("Fat Burn");
	protected HeartRateZone cardio = new HeartRateZone("Cardio");
	protected HeartRateZone peak = new HeartRateZone("Peak");
	protected FitCalcActivity[] recentActivities = new FitCalcActivity[3];


	/**
	 * This refresh method will only return the time
	 * That the user pressed the button, since it might 
	 * possibly not be an APIData object, which
	 * in that case new values will not be gotten
	 * @return
	 */
	public String refresh() {
		Calendar cal = Calendar.getInstance();
		SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
		return sdf.format(cal.getTime());
	}


	/**
	 * Method that will return the calories out
	 * @return The APIData's attribute Calories Out; which is an Activity type
	 */
	public Activity getCaloriesOut() {
		return caloriesOut;
	}
	/**
	 * Method that will return the floors
	 * @return The APIData's attribute floors; which is an Activity type
	 */
	public Activity getFloors() {
		return floors;
	}
	/**
	 * Method that will return the steps
	 * @return The APIData's attribute steps; which is an Activity type
	 */
	public Activity getSteps() {
		return steps;
	}
	/**
	 * Method that will return the active minutes
	 * @return The APIData's attribute active minutes; which is an Activity type
	 */
	public Activity getActMin() {
		return actMin;
	}
	/**
	 * Method that will return sedentary minutes
	 * @return The APIData's attribute sedentary minutes; which is an Activity type
	 */
	public Activity getSedMin() {
		return sedMin;
	}
	/**
	 * Method that will return distance
	 * @return The APIData's attribute distance; which is an Activity type
	 */
	public Activity getDistance() {
		return distance;
	}
	/**
	 * Method that will return the best distance
	 * @return The APIData's attribute best distance; which is a BestActivity type
	 */
	public BestActivity getBestDistance() {
		return bestDistance;
	}
	/**
	 * Method that will return the best floors
	 * @return The APIData's attribute best floors; which is a BestActivity type
	 */
	public BestActivity getBestFloors() {
		return bestFloors;
	}
	/**
	 * Method that will return the best steps
	 * @return The APIData's attribute best steps; which is a BestActivity type
	 */
	public BestActivity getBestSteps() {
		return bestSteps;
	}
	/**
	 * Method that will return the total distance
	 * @return The APIData's attribute total distance; which is an Activity type
	 */
	public Activity getTotalDistance() {
		return totalDistance;
	}
	/**
	 * Method that will return the total floors
	 * @return The APIData's attribute total floors; which is an Activity type
	 */
	public Activity getTotalFloors() {
		return totalFloors;
	}
	/**
	 * Method that will return the total steps
	 * @return The APIData's attribute total steps; which is an Activity type
	 */
	public Activity getTotalSteps() {
		return totalSteps;
	}
	/**
	 * Method that will return the resting heart rate
	 * @return The APIData's attribute resting heart rate; which is an Activity type
	 */
	public Activity getRestingHeartRate() {
		return restingHeartRate;
	}
	/**
	 * Method that will return the out of range zone
	 * @return The APIData's attribute out of range zone; which is a HeartRateZone type
	 */
	public HeartRateZone getOutOfRange() {
		return outOfRange;
	}
	/**
	 * Method that will return the fat burn zone
	 * @return The APIData's attribute fat burn zone; which is a HeartRateZone type
	 */
	public HeartRateZone getFatBurn() {
		return fatBurn;
	}
	/**
	 * Method that will return the cardio zone
	 * @return The APIData's attribute cardio; which is a HeartRateZone type
	 */
	public HeartRateZone getCardio() {
		return cardio;
	}
	/**
	 * Method that will return the peak zone
	 * @return The APIData's attribute peak; which is a HeartRateZone type
	 */
	public HeartRateZone getPeak() {
		return peak;
	}
	public FitCalcActivity[] getRecentActivities() {
		return recentActivities;
	}

}
