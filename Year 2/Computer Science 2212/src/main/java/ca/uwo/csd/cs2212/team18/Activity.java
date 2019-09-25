package ca.uwo.csd.cs2212.team18;
/**
 * The Activity class creates Activity objects that will store the name and value of 
 * a certain activity
 * @author Team 18 
 *
 */
public class Activity {
	private String type;
	private int value;
	/**
	 * 
	 * @param type is passed in to store the object's type
	 */
	public Activity(String type){
		this.type = type;
	}

	/**
	 * This method will return the type
	 * @return returns the Activity object's type
	 */
	public String getType() {
		return type;
	}
	/**
	 * This method will return the value
	 * @return returns the Activity object's value
	 */
	public int getValue() {
		return value;
	}

	/**
	 * This method will set the value of the Activity object
	 * @param value will set the Activity object's value
	 */
	public void setValue(int value) {
		this.value = value;
	}
	
	public void setType(String type) {
		this.type = type;
	}

}
