package ca.uwo.csd.cs2212.team18;
/**
 * Extends the Activity Class to include 
 * data for fit calc activities, which
 * stores the mets as well
 * @author Team 18 
 *
 */
public class FitCalcActivity extends Activity {
	private double mets;
	
	/**
	 * Constructor method for the FitCalcActivity object
	 * @param type Is the name of the activity
	 * @param value Is the value of the activity
	 */
	public FitCalcActivity(String type, int value){
		super(type);
		this.setValue(value);
	}

	/**
	 * Sets the mets
	 * @param mets is to determine the value of calorie burn for the activity
	 */
	public void setMets(double mets) {
		this.mets = mets;
	}

	/**
	 * Gets the mets
	 * @return the mets attribute which is used to determine the value of calorie burn for the 
	 * activity
	 */
	public double getMets() {
		return mets;
	}
}
