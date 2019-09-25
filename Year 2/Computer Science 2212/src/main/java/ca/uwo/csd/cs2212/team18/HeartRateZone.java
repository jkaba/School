package ca.uwo.csd.cs2212.team18;

/**
 * Extends the activity class for 
 * HeartRateZone objects by adding descriptions,
 * minutes, and minimum and maximum values
 * @author Team 18 
 *
 */
public class HeartRateZone extends Activity{

	/* private variable */
	/**
	 * Integer variable representing the minimum heart rate
	 */
	private int min;

	/**
	 * Integer variable representing the maximum heart rate
	 */
	private int max;

	/**
	 * String representing the description of the heart rate
	 */
	private String description;

	/**
	 * Constructor that creates a new heart rate zone 
	 * @param type The type of heart rate zone
	 */
	public HeartRateZone(String type){
		super(type);
	}

	/**
	 * Getter method to get the minimum heart rate
	 * @return minimum
	 */
	public int getMin() {
		return min;
	}

	/**
	 * Setter method to set the minimum heart rate
	 * @param min The new minimum heart rate
	 */
	public void setMin(int min) {
		this.min = min;
	}

	/**
	 * Getter method to get the maximum heart rate
	 * @return The maximum heart rate
	 */
	public int getMax() {
		return max;
	}

	/**
	 * Setter method to set the maximum heart rate
	 * @param max The maximum heart rate
	 */
	public void setMax(int max) {
		this.max = max;
	}

	/**
	 * Getter method to get the Description
	 * @return The description
	 */
	public String getDescription() {
		return description;
	}

	/**
	 * Setter method to set the description
	 * @param description The new description
	 */
	public void setDescription(String description) {
		this.description = description;
	}
	
}
