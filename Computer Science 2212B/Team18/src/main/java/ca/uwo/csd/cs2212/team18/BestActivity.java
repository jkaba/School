package ca.uwo.csd.cs2212.team18;
/**
 * Extends the Activity Class to include date that stat was achieved
 * @author Team 18 
 */
public class BestActivity extends Activity{

	private String date;
	/**
	 * This method will create a BestActivity type that is an extension of the activity type
	 * @param type will set the object's type variable
	 */
	public BestActivity(String type) {
		super(type);
	}

	/**
	 * This method will return the date of the BestActivity's object
	 * @return returns the date of the object
	 */
	public String getDate() {
		return date;
	}

	/**
	 * This method will set the BestActivity object's date
	 * @param date will set the object's date
	 */
	public void setDate(String date) {
		this.date = date;
	}


}
