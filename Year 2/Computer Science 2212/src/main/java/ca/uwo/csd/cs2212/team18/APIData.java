package ca.uwo.csd.cs2212.team18;


import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;


import com.github.scribejava.apis.FitbitApi20;
import com.github.scribejava.apis.service.FitbitOAuth20ServiceImpl;
import com.github.scribejava.core.builder.ServiceBuilder;
import com.github.scribejava.core.exceptions.OAuthConnectionException;
import com.github.scribejava.core.model.*;

import org.json.JSONException;
import org.json.JSONObject;
import org.json.JSONArray;
/**
 * The purpose of this class is to create objects that will access the
 * Fitbit's API servers via Oauthentication 2 and will parse through the resulting
 * JSON texts and store the various values for each of the object's attributes
 * @author Team 18 
 *
 */
public class APIData extends Data{

	/**
	 * Declare constants
	 */

	static final String REQUEST_URL_PREFIX = "https://api.fitbit.com/1/user/3WGW2P/";
	static final String CALL_BACK_URL="http://localhost:8080";
	static final String SCOPE = "activity%20heartrate";


	// String variables that will store the different urls that will access the information
	// from the APIData
	private String requestUrlActivities;
	private String requestUrlHeartRate;
	private String requestUrlBestLife;
	private String requestUrlRecentActivities;


	// Variables used to store authentication information
	private OAuth2AccessToken accessToken;
	private FitbitOAuth20ServiceImpl service;
	private Response response;


	//private String apiKey = null;
	private String apiSecret = null;
	private String clientID = null;
	private String accessTokenItself = null;
	private String tokenType = null;
	private String refreshToken = null;
	private Long expiresIn = null;
	private String rawResponse = null;
	private boolean errorConnection = false;


	/**
	 * This constructor allows a date to be used as a parameter in order to access the Fitbit's 
	 * API for a specific date
	 * @param date The String parameter date is used to choose the date that the APIData class will
	 * access from Fitbit API servers in order to fill the object's attributes
	 */
	public APIData(String date){
		readFiles();

		//  Create the Fitbit service - you will ask this to ask for access/refresh pairs
		//     and to add authorization information to the requests to the API
		service = (FitbitOAuth20ServiceImpl) new ServiceBuilder()
				.apiKey(clientID)       //fitbit uses the clientID here
				.apiSecret(apiSecret)
				.callback(CALL_BACK_URL)
				.scope(SCOPE)
				.grantType("authorization_code")
				.build(FitbitApi20.instance());

		//  The access token contains everything you will need to authenticate your requests
		//  It can expire - at which point you will use the refresh token to refresh it
		//    I have authenticated and given you the contents of the response to use
		accessToken = new OAuth2AccessToken(
				accessTokenItself,
				tokenType,
				refreshToken,
				expiresIn,
				rawResponse);

		// Method that will create the request urls based on the date
		createRequests(date);
	}



	/**
	 * A helper method that will create the request urls and sent for the requests
	 * @param date the string parameter date is used to choose the date that the api requests
	 * will access from Fitbit API servers
	 */
	private void createRequests(String date){


		try {
			// Builds the strings to request for specific information from the API
			requestUrlActivities = REQUEST_URL_PREFIX + "activities/date/" + date + ".json";
			requestUrlHeartRate = REQUEST_URL_PREFIX + "activities/heart/date/" + date + "/1d.json";
			requestUrlBestLife = REQUEST_URL_PREFIX + "activities.json";
			requestUrlRecentActivities = REQUEST_URL_PREFIX + "activities/recent.json";


			// Calls methods that will pull information from the API and store them
			// in the appropriate attributes
			setActivities();
			setBestLife();
			setHeartRate();
			setRecentActivity();
			save();
		}catch(OAuthConnectionException e){
			connectionError();
		}
	}

	/**
	 * Private method that will set all the attributes of the APIData object to invalid
	 * values
	 */
	private void connectionError(){
		errorConnection = true;
		caloriesOut.setValue(-1);
		floors.setValue(-1);
		steps.setValue(-1);
		actMin.setValue(-1);
		sedMin.setValue(-1);
		distance.setValue(-1);
		restingHeartRate.setValue(-1);
		bestDistance.setValue(-1);
		bestDistance.setDate("Not Available");
		bestFloors.setValue(-1);
		bestFloors.setDate("Not Available");
		bestSteps.setValue(-1);
		bestSteps.setDate("Not Available");
		totalDistance.setValue(-1);
		totalFloors.setValue(-1);
		totalSteps.setValue(-1);
		outOfRange.setValue(-1);
		fatBurn.setValue(-1);
		cardio.setValue(-1);
		peak.setValue(-1);
		for (int i = 0; i < recentActivities.length; i++){
			recentActivities[i] = new FitCalcActivity("Not Available", -1);
			recentActivities[i].setValue(-1);
		}
	}


	/**
	 * Private method that reads the credentials and tokens
	 * files in order to authenticate the users credentials
	 * and allow Fitbit information to be attained
	 */
	private void readFiles(){
		BufferedReader bR = null;
		try {

			// Stores various user authentication information variables from
			// the Team18Credentials.txt and Team18Tokens.txt files
			FileReader fileReader =
					new FileReader("src/main/resources/Team18Credentials.txt");   
			bR = new BufferedReader(fileReader);
			clientID = bR.readLine();
			bR.readLine();
			apiSecret = bR.readLine();
			bR.close();
			fileReader = new FileReader("src/main/resources/Team18Tokens.txt");
			bR = new BufferedReader(fileReader);

			accessTokenItself = bR.readLine();
			tokenType = bR.readLine();
			refreshToken = bR.readLine();
			expiresIn = Long.parseLong(bR.readLine());
			rawResponse = bR.readLine();

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

	/**
	 * Private method that will write the new tokens
	 * to the tokens file
	 */
	private void writeFiles() {
		BufferedWriter bW = null;
		try {
			// Will store the new access/refresh tokens in the 
			// appropriate file
			FileWriter fileWriter = 
					new FileWriter("src/main/resources/Team18Tokens.txt");
			bW = new BufferedWriter(fileWriter);
			bW.write(accessToken.getToken());
			bW.newLine();
			bW.write(accessToken.getTokenType());
			bW.newLine();
			bW.write(accessToken.getRefreshToken());
			bW.newLine();
			bW.write(accessToken.getExpiresIn().toString());
			bW.newLine();
			bW.write(accessToken.getRawResponse());
			bW.newLine();
			bW.close();
		} catch(FileNotFoundException ex){
		} catch(IOException ex) { 
		} finally {
			try {
				if (bW != null)
					bW.close(); 
			} catch(Exception e) {
			}
		}
	}

	/**
	 * private method that will store the values 
	 * of the APIData object to a file 
	 * so that the test mode has values 
	 */
	private void save(){
		BufferedWriter bW = null;
		try {
			FileWriter fileWriter =
					new FileWriter("src/main/resources/Data.txt");
			bW = new BufferedWriter(fileWriter);
			bW.write(String.valueOf(caloriesOut.getValue()));
			bW.newLine();
			bW.write(String.valueOf(floors.getValue()));
			bW.newLine();
			bW.write(String.valueOf(steps.getValue()));
			bW.newLine();
			bW.write(String.valueOf(actMin.getValue()));
			bW.newLine();
			bW.write(String.valueOf(sedMin.getValue()));
			bW.newLine();
			bW.write(String.valueOf(distance.getValue()));
			bW.newLine();
			bW.write(String.valueOf(bestDistance.getValue()));
			bW.newLine();
			bW.write(bestDistance.getDate());
			bW.newLine();
			bW.write(String.valueOf(bestFloors.getValue()));
			bW.newLine();
			bW.write(bestFloors.getDate());
			bW.newLine();
			bW.write(String.valueOf(bestSteps.getValue()));
			bW.newLine();
			bW.write(bestSteps.getDate());
			bW.newLine();
			bW.write(String.valueOf(totalDistance.getValue()));
			bW.newLine();
			bW.write(String.valueOf(totalFloors.getValue()));
			bW.newLine();
			bW.write(String.valueOf(totalSteps.getValue()));
			bW.newLine();
			bW.write(String.valueOf(restingHeartRate.getValue()));
			bW.newLine();
			bW.write(String.valueOf(outOfRange.getValue()));
			bW.newLine();
			bW.write(String.valueOf(fatBurn.getValue()));
			bW.newLine();
			bW.write(String.valueOf(cardio.getValue()));
			bW.newLine();
			bW.write(String.valueOf(peak.getValue()));
			bW.newLine();
			for (int i =0; i < recentActivities.length; i++){
				bW.write(recentActivities[i].getType());
				bW.newLine();
				bW.write(String.valueOf(recentActivities[i].getValue()));
				bW.newLine();
				bW.write(String.valueOf(recentActivities[i].getMets()));
				bW.newLine();
			}
			bW.close();
		} catch(FileNotFoundException ex){
		} catch(IOException ex) {  
		} finally {
			try {
				if (bW != null)
					bW.close(); 
			} catch(Exception e) {
			}
		}
	}
	
	/**
	 * The api method is a private helper method that will access the Fitbit's API
	 * via OAuthentication and will store the JSON objects that are returned
	 * @param requestUrl The String parameter that stores the specific URL that the 
	 * api method should access in order to store the JSON object that will contain the APIData's
	 * attributes
	 */
	private void api(String requestUrl) {
		// Initializes OAuthRequest object specific to the passed in URL
		OAuthRequest request = new OAuthRequest(Verb.GET, requestUrl, service);

		service.signRequest(accessToken, request);

		response = request.send();

		int statusCode = response.getCode();

		/*
		 * 200: Authentication successful
		 * 400: Invalid URL request
		 * 401: Possibly expired tokens, will attempt to gain new 
		 * 		pair by using refresh token
		 * 429: Too many API requests have been issued
		 */
		switch(statusCode){
		case 200:
			errorConnection = false;
			break;
		case 400:
			break;
		case 401:
			accessToken = service.refreshOAuth2AccessToken(accessToken);
			request = new OAuthRequest(Verb.GET, requestUrl, service);
			service.signRequest(accessToken, request);
			response = request.send();
			writeFiles();
			break;
		case 429:
			errorConnection = true;
			break;
		}

	}


	/**
	 * The setActivites method is a private helper method that will parse through
	 * the current response body that contains the JSON information for the APIData object's
	 * Activity attributes.
	 * This includes the attributes Calories Out, Floors, Steps, Active Minutes, Sedentary
	 * Minutes, and Distance 
	 */
	private void setActivities(){
		// Parses through the JSON text and save the values in the
		// appropriate attributes
		try {
			api(requestUrlActivities);
			JSONObject jsonObj = new JSONObject(response.getBody());
			JSONArray jsonArray;
			jsonObj = jsonObj.getJSONObject("summary");
			caloriesOut.setValue(jsonObj.getInt("caloriesOut"));
			floors.setValue(jsonObj.getInt("floors"));
			steps.setValue(jsonObj.getInt("steps"));
			actMin.setValue(jsonObj.getInt("fairlyActiveMinutes") + jsonObj.getInt("lightlyActiveMinutes") + jsonObj.getInt("veryActiveMinutes"));
			sedMin.setValue(jsonObj.getInt("sedentaryMinutes"));
			jsonArray = jsonObj.getJSONArray("distances");
			jsonObj = jsonArray.getJSONObject(0);
			distance.setValue((int)jsonObj.getDouble("distance"));
		} catch (JSONException e) {
			connectionError();
		}
	}

	/**
	 * The setBestLife method is a private helper method that will parse through the
	 * current response body that contains the JSON information for the APIData object's
	 * Best Dates and Total Life activities.
	 * This includes the attributes Best Distance, Best Steps, Best Floors, Total Distance,
	 * Total Steps, and Total Floors
	 */
	private void setBestLife(){
		// Parses through the JSON text and save the values in the
		// appropriate attributes
		try {
			api(requestUrlBestLife);

			JSONObject jsonBest, jsonLife, jsonDistance, jsonSteps, jsonFloors;
			JSONObject jsonObj = new JSONObject(response.getBody());
			jsonBest = jsonObj;
			jsonBest = jsonBest.getJSONObject("best");
			jsonBest = jsonBest.getJSONObject("total");
			jsonDistance = jsonBest.getJSONObject("distance");
			jsonSteps = jsonBest.getJSONObject("steps");
			jsonFloors = jsonBest.getJSONObject("floors");
			bestDistance.setValue(jsonDistance.getInt("value"));
			bestDistance.setDate(jsonDistance.getString("date"));
			bestSteps.setValue(jsonSteps.getInt("value"));
			bestSteps.setDate(jsonSteps.getString("date"));
			bestFloors.setValue(jsonFloors.getInt("value"));
			bestFloors.setDate(jsonFloors.getString("date"));
			jsonLife = jsonObj;
			jsonLife = jsonLife.getJSONObject("lifetime");
			jsonLife = jsonLife.getJSONObject("total");
			totalDistance.setValue(jsonLife.getInt("distance"));
			totalSteps.setValue(jsonLife.getInt("steps"));
			totalFloors.setValue(jsonLife.getInt("floors"));

		} catch (JSONException e) {
			connectionError();
		}
	}

	/**
	 * The setHeartRate method is a private helper method that will parse through the
	 * current response body that contains the JSON information for the APIData object's
	 * Heart Rate information.
	 * This includes the attributes Resting Heart Rate, Out of Range Zone, Fat Burn Zone,
	 * Cardio Zone, and Peak Zone
	 */
	private void setHeartRate(){
		// Parses through the JSON text and save the values in the
		// appropriate attributes
		try {
			api(requestUrlHeartRate);
			JSONObject jsonObj = new JSONObject(response.getBody());
			JSONObject jsonOutOfRange, jsonFatBurn, jsonCardio,  jsonPeak; 
			JSONArray jsonArray;
			jsonArray = jsonObj.getJSONArray("activities-heart");
			jsonObj = jsonArray.getJSONObject(0);
			jsonObj = jsonObj.getJSONObject("value");
			restingHeartRate.setValue(jsonObj.getInt("restingHeartRate"));
			jsonArray = jsonObj.getJSONArray("heartRateZones");
			jsonOutOfRange = jsonArray.getJSONObject(0);
			jsonFatBurn = jsonArray.getJSONObject(1);
			jsonCardio = jsonArray.getJSONObject(2);
			jsonPeak = jsonArray.getJSONObject(3);


		} catch (JSONException e) {
			restingHeartRate.setValue(-1);
			outOfRange.setValue(-1);
			fatBurn.setValue(-1);
			cardio.setValue(-1);
			peak.setValue(-1);
		}
	}

	/**
	 * The setRecentActivity method is a private method that will parse through
	 * the current nresponse body that contains the JSON information for the APIData object's
	 * Heart Rate information
	 * This includes the 3 most recent activities and they will be stored into an array
	 */
	private void setRecentActivity() {
		try{
			api(requestUrlRecentActivities);
			final String REQUEST_URL_RECENT_ACTIVITY_PREFIX = "https://api.fitbit.com/1/activities/";
			String requestUrlRecentActivity;
			JSONArray jsonArray2 = new JSONArray(response.getBody());
			JSONArray jsonArray;
			JSONObject jsonObj;
			for (int i = 0; i < recentActivities.length; i++){
				jsonObj = jsonArray2.getJSONObject(i);
				recentActivities[i] = new FitCalcActivity(jsonObj.getString("name"),jsonObj.getInt("activityId"));
				requestUrlRecentActivity = REQUEST_URL_RECENT_ACTIVITY_PREFIX + recentActivities[i].getValue() + ".json";
				api(requestUrlRecentActivity);
				try {
					jsonObj = new JSONObject(response.getBody());
					jsonObj = jsonObj.getJSONObject("activity");
					jsonArray = jsonObj.getJSONArray("activityLevels");
					jsonObj = jsonArray.getJSONObject(0);
					recentActivities[i].setMets(jsonObj.getDouble("mets"));
				}catch (JSONException e){
					recentActivities[i].setMets(jsonObj.getDouble("mets"));
				}
			}
		}catch (JSONException e){
			connectionError();
		}
	}

	/**
	 * The setHRObject method is a private helper method that will pass in a Heart Rate Zone object to be
	 * filled as well as a JSONObject that will be used to extract the values that will fill
	 * the attributes.
	 * @param obj This parameter will be the HeartRateZone object to be filled with the values
	 * from the JSONObject
	 * @param jsonObj This parameter will be the JSONObject that contains the JSON text that contains
	 * the appropriate values to be stored in the HeartRateZone object that is passed in
	 */
	private void setHRObject(HeartRateZone obj, JSONObject jsonObj) {
		try {
			// Sets the attributes of the heart rate zone object using the JSON object
			obj.setMin(jsonObj.getInt("min"));
			obj.setMax(jsonObj.getInt("max"));
			obj.setValue(jsonObj.getInt("minutes"));
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * The refresh method will refresh the attributes of the APIData object with 
	 * information and values from a different date
	 * @param date This parameter is a String which indicates the new date which 
	 * should be now pulled from the Fitbit's API server
	 * @return The current time in the format of HH:mm:ss in order to indicate
	 * the time that a refresh for new information was requested
	 */
	public String refresh(String date) {

		// Calls the methods that will pull information and store them in the
		// appropriate attributes
		createRequests(date);

		return super.refresh();
	}

	/**
	 * Method that will return the value indicating wether there was 
	 * a error connecting with the api
	 * @return errorConnection which is a boolean value
	 * that stores whether or not there was an api error
	 */
	public boolean isErrorConnection() {
		return errorConnection;
	}
}


