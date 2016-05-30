package ca.uwo.csd.cs2212.team18;

/**
 * Accolades class used for determining which accolades have been met, 
 * and which accolades have not been met. 
 * @author Team 18
 *
 */
public class Accolades {

	/**
	 * Constructor to make an instance of the accolades class
	 */
	public Accolades(){

	}


	/**
	 * Complete method that checks to see which accolades have been met. 
	 * @param dat The Data to be used for the checks
	 * @param test Boolean value that determines whether test data or dat data is used
	 * @return A Boolean array which has elements set to true if the goal was met, elements set to false otherwise
	 */
	public static Boolean[] complete(Data dat, Boolean test){

		// If test is true then use Test Data
		if(test == true){
			dat = new TestData();
		}

		// Else test is false, so use API Data
		else{
			dat = (APIData) dat;
		}

		// Create a Boolean array to store the true/false values
		final Boolean[] comp = new Boolean[20];

		// Dubai [Burj Khalifa] (272 floors)
		if(dat.getTotalFloors().getValue() >= 272){
			comp[0] = true;
		}

		// Else The Accolade was not met
		else{	
			comp[0] = false;
		}

		// 10 floors
		if(dat.getTotalFloors().getValue() >= 10){
			comp[1] = true;
		}

		// Else The Accolade was not met
		else{	
			comp[1] = false;
		}

		// Climb 1000 floors
		if(dat.getTotalFloors().getValue() >= 1000){
			comp[4] = true;
		}

		// Else The Accolade was not achieved
		else{
			comp[4] = false;
		}

		// Left the House (200 steps)
		if(dat.getTotalSteps().getValue() >= 200){
			comp[3] = true;
		}

		// Else the Accolade was not achieved
		else{
			comp[3] = false;
		}

		// Stairway to Heaven (all floor accolades)
		if(comp[0] == true && comp[1] == true && comp[4] == true){	
			comp[2] = true;
		}

		// Else The Accolade was not achieved
		else{
			comp[2] = false;
		}

		// Over 9000 (9000 steps)
		if(dat.getTotalSteps().getValue() >= 9000){			
			comp[5] = true;
		}

		// Else the Accolade was not achieved
		else{
			comp[5] = false;
		}

		// Back to back (10000 steps)
		if(dat.getTotalSteps().getValue() >= 10000){
			comp[6] = true;
		}

		// Else the Accolade was not achieved
		else{
			comp[6] = false;
		}

		// The beginning of the end (1000 calories)
		if(dat.getCaloriesOut().getValue() >= 1000){
			comp[7] = true;
		}

		// Else the Accolade was not achieved
		else{
			comp[7] = false;
		}

		// Devilish Delight (2420 calories)
		if(dat.getCaloriesOut().getValue() >= 2420){
			comp[8] = true;
		}

		// Else the Accolade was not achieved
		else{
			comp[8] = false;
		}

		// Cereal Killer (379 calories)
		if(dat.getCaloriesOut().getValue() >= 379){
			comp[9] = true;
		}

		// Else the Accolade was not achieved
		else{
			comp[9] = false;
		}

		// Cold Hearted Murderer (5200 calories)
		if(dat.getCaloriesOut().getValue() >= 5200){
			comp[10] = true;
		}

		// Else the accolade was not met
		else{
			comp[10] = false;
		}

		// Distance around the world (40075 km)
		if(dat.getTotalDistance().getValue() >= 40075){
			comp[11] = true;
		}

		// Else the accolade was not met
		else{
			comp[11] = false;
		}

		// Walked around the earth (131480184 steps)
		if(dat.getTotalSteps().getValue() >= 131480184){
			comp[12] = true;
		}

		// Else the Accolade was not achieved
		else{
			comp[12] = false;
		}

		// Fat Burner (3500 calories)
		if(dat.getCaloriesOut().getValue() >= 3500){
			comp[13] = true;
		}

		// Else the accolade was not met
		else{
			comp[13] = false;
		}

		// Mass Destruction (7500 calories)
		if(dat.getCaloriesOut().getValue() >= 7500){
			comp[14] = true;
		}

		// Else the accolade was not met 
		else{
			comp[14] = false;
		}

		// Walked a mile (1.60934 km)
		if(dat.getTotalDistance().getValue() >= 1.60934){
			comp[15] = true;
		}

		// Else the accolade was not met
		else{
			comp[15] = false;
		}

		// Distance to the moon (384400 km)
		if(dat.getTotalDistance().getValue() >= 384400){
			comp[16] = true;
		}

		// Else the accolade was not met
		else{
			comp[16] = false;
		}

		// Breaking into your shoes (1000 steps)
		if(dat.getTotalSteps().getValue() >= 1000){			
			comp[17] = true;
		}

		// Else the Accolade was not achieved
		else{			
			comp[17] = false;
		}


		// From Fanshawe to Western (6.2 km)
		if(dat.getTotalDistance().getValue() >= 6.2){
			comp[18] = true;
		}

		// Else the goal was not met
		else{	
			comp[18] = false;
		}

		// Masonville to White Oaks (12.2 km)
		if(dat.getTotalDistance().getValue() >= 12.2){
			comp[19] = true;
		}

		// Else the accolade was not met
		else{	
			comp[19] = false;
		}

		// Return the Boolean array to determine which goals have been met
		return comp;
	}

}
