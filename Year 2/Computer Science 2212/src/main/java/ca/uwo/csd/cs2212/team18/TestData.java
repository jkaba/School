package ca.uwo.csd.cs2212.team18;


import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
/**
 * The purpose of this class is to create objects that will access the
 * the text file Data.txt and store the various values for each of the object's attributes
 * @author Team 18 
 *
 */

public class TestData extends Data{

	/**
	 * Constructor for the Test Data object
	 */
	public TestData(){
		load();
	}
	
	/**
	 * private method that will load the data.txt file and add it's values to the
	 * appropriate attributes
	 */
	private void load(){
		BufferedReader bR = null;
		try {

			FileReader fileReader =
					new FileReader("src/main/resources/Data.txt");   
			bR = new BufferedReader(fileReader);
			caloriesOut.setValue(Integer.parseInt(bR.readLine()));
			floors.setValue(Integer.parseInt(bR.readLine()));
			steps.setValue(Integer.parseInt(bR.readLine()));
			actMin.setValue(Integer.parseInt(bR.readLine()));
			sedMin.setValue(Integer.parseInt(bR.readLine()));
			distance.setValue(Integer.parseInt(bR.readLine()));
			bestDistance.setValue(Integer.parseInt(bR.readLine()));
			bestDistance.setDate(bR.readLine());
			bestFloors.setValue(Integer.parseInt(bR.readLine()));
			bestFloors.setDate(bR.readLine());
			bestSteps.setValue(Integer.parseInt(bR.readLine()));
			bestSteps.setDate(bR.readLine());
			totalDistance.setValue(Integer.parseInt(bR.readLine()));
			totalFloors.setValue(Integer.parseInt(bR.readLine()));
			totalSteps.setValue(Integer.parseInt(bR.readLine()));
			restingHeartRate.setValue(Integer.parseInt(bR.readLine()));
			outOfRange.setValue(Integer.parseInt(bR.readLine()));
			fatBurn.setValue(Integer.parseInt(bR.readLine()));
			cardio.setValue(Integer.parseInt(bR.readLine()));
			peak.setValue(Integer.parseInt(bR.readLine()));
			for (int i = 0; i < recentActivities.length; i++){
				recentActivities[i] = new FitCalcActivity(bR.readLine(), Integer.parseInt(bR.readLine()));
				recentActivities[i].setMets(Double.parseDouble(bR.readLine()));
			}
			bR.close();
			

		}
		// Handles exception if the file is not found
		catch(FileNotFoundException ex) {

			System.exit(1);
		}
		// Handles exception if the file's text formating is incorrect
		catch(IOException ex) {
  
			System.exit(1);
		}
		finally{
			try{
				if (bR!=null)
					// Always close files.
					bR.close(); 
			}
			catch(Exception e){

			}
		}
	}
}
