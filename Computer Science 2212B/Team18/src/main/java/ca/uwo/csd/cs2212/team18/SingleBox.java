package ca.uwo.csd.cs2212.team18;

// Import needed files
import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

/**
 * Class that creates various tiles that are on the basedashboard
 * @author Team18
 *
 */
public class SingleBox{

	// Initialize fonts and color
	Font font = new Font("Arial", Font.PLAIN, 18);
	Font font2 = new Font("Arial", Font.BOLD, 12);
	Font font3 = new Font("Arial", Font.BOLD, 13);
	Font apiFont = new Font("Arial", Font.BOLD, 34);
	Color blueColour = Color.decode("#45C2C5");

	DateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");

	// Get current date time with Date()
	Date date = new Date();
	String fulldate = dateFormat.format(date);
	String curYear = fulldate.substring(0,4);
	String curMonth = fulldate.substring(4,6);
	String curDay = fulldate.substring(6,8);

	// Put the date value together 
	String apiInput = "";
	{
		apiInput = apiInput.concat(curYear);
		apiInput = apiInput.concat("-");
		apiInput = apiInput.concat(curMonth);
		apiInput = apiInput.concat("-");
		apiInput = apiInput.concat(curDay);
	}

	// Create JLabel with updated information
	static JLabel calString = new JLabel();
	static JLabel activeString = new JLabel();
	static JLabel sedString = new JLabel();
	static JLabel distanceDailyString = new JLabel();
	static JLabel distanceBestString = new JLabel();
	static JLabel distanceTotalString = new JLabel();
	static JLabel floorDailyString = new JLabel();
	static JLabel floorBestString = new JLabel();
	static JLabel floorTotalString = new JLabel();
	static JLabel stepDailyString = new JLabel();
	static JLabel stepBestString = new JLabel();
	static JLabel stepTotalString = new JLabel();

	// Constructor
	public SingleBox(){
	} 


	// Set new string for activities
	static int caloriesOut;
	static int floorDailyOut;
	static int floorBestOut;
	static int floorTotalOut;
	static int stepDailyOut;
	static int stepBestOut;
	static int stepTotalOut;
	static int activeOut;
	static int sedOut;
	static int distanceDailyOut;
	static int distanceBestOut;
	static int distanceTotalOut;

	// Set new string for activities
	static Data apiData;
	static APIData notTest;
	private static boolean test;

	// Method that checks to run in default or API values
	public void setTestOrNot(boolean testorNot) {
		test = testorNot;
	}
	public void passAPI(Data api, boolean testorNot) {

		apiData = api;
		if (testorNot == false) {
			notTest = (APIData) apiData;
		}
	}
	// Method to update the API
	public void updateAPI(String dateInput) {
		if (test == true) {
		} else {
			notTest = (APIData) apiData; 
			notTest.refresh(dateInput);
		}
	}
	public Data returnAPI() {
		return notTest;
	}

	// Method to update the API data
	public void updateTilesVars() {
		if (test == true) {
			caloriesOut = (int) apiData.getCaloriesOut().getValue();
			floorDailyOut = (int) apiData.getFloors().getValue();
			floorBestOut = (int) apiData.getBestFloors().getValue();
			floorTotalOut = (int) apiData.getTotalFloors().getValue();
			stepDailyOut = (int) apiData.getSteps().getValue();
			stepBestOut = (int) apiData.getBestSteps().getValue();
			stepTotalOut = (int) apiData.getTotalSteps().getValue();
			activeOut = (int) apiData.getActMin().getValue();
			sedOut = (int) apiData.getSedMin().getValue();
			distanceDailyOut = (int) apiData.getDistance().getValue();
			distanceBestOut = (int) apiData.getBestDistance().getValue();
			distanceTotalOut = (int) apiData.getTotalDistance().getValue();
		} else {
			caloriesOut = (int) notTest.getCaloriesOut().getValue();
			floorDailyOut = (int) notTest.getFloors().getValue();
			floorBestOut = (int) notTest.getBestFloors().getValue();
			floorTotalOut = (int) notTest.getTotalFloors().getValue();
			stepDailyOut = (int) notTest.getSteps().getValue();
			stepBestOut = (int) notTest.getBestSteps().getValue();
			stepTotalOut = (int) notTest.getTotalSteps().getValue();
			activeOut = (int) notTest.getActMin().getValue();
			sedOut = (int) notTest.getSedMin().getValue();
			distanceDailyOut = (int) notTest.getDistance().getValue();
			distanceBestOut = (int) notTest.getBestDistance().getValue();
			distanceTotalOut = (int) notTest.getTotalDistance().getValue();
		}
	}


	/**
	 *  Method used to produce API Data
	 */
	public void modifyString(int kindBox) {
		if (kindBox == 0) {
			calString.setText(String.valueOf(caloriesOut));
		}
		if (kindBox == 1) {
			floorDailyString.setText(String.valueOf(floorDailyOut));
			floorBestString.setText(String.valueOf(floorBestOut));
			floorTotalString.setText(String.valueOf(floorTotalOut));
		}
		if (kindBox == 2) {		
			stepDailyString.setText(String.valueOf(stepDailyOut));
			stepBestString.setText(String.valueOf(stepBestOut));
			stepTotalString.setText(String.valueOf(stepTotalOut));
		}
		if (kindBox == 3) {
			activeString.setText(String.valueOf(activeOut));
			sedString.setText(String.valueOf(sedOut));
		}
		if (kindBox == 4) {
			distanceDailyString.setText(String.valueOf(distanceDailyOut));
			distanceBestString.setText(String.valueOf(distanceBestOut));
			distanceTotalString.setText(String.valueOf(distanceTotalOut));
		}
	}

	/**
	 * Method will create a box with Calories information
	 * @return JPanel with Calories
	 */
	public JPanel createCaloriesBox() {

		// Initialize variables
		JLabel nameLabel = new JLabel("Daily Calories Burned");
		JButton xSignButton = new JButton("x");
		final JPanel paneName = new JPanel();

		// Setup how x button will look
		xSignButton.setFont(font);
		xSignButton.setLayout(null);
		xSignButton.setForeground(blueColour);
		//xSignButton.setBorder(null);
		xSignButton.setBounds(1,1,20,20);

		// Setup how label will look like
		nameLabel.setFont(font3);
		nameLabel.setForeground(blueColour);
		nameLabel.setBounds(25,-12,500,50);

		// Setup how calString will look like
		calString.setFont(apiFont);
		calString.setForeground(blueColour);
		calString.setBounds(40,70,500,50);

		// Setup how pane box will look like
		paneName.setLayout(null);
		paneName.setBackground(Color.WHITE);
		paneName.setVisible(true);
		paneName.add(calString);
		paneName.add(xSignButton);
		paneName.add(nameLabel, SwingConstants.CENTER);

		// Adding action when x button is pressed
		// Close the pane when pressed
		xSignButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				paneName.setVisible(false);
				BaseDashBoardUI.getFrame().remove(paneName);
				BaseDashBoard.addClosedTile("Calories");
			}
		});
		paneName.add(xSignButton);
		return paneName;
	}

	/**
	 * Method will create a box with Active and Sedentary information
	 * @return JPanel with Active and Sedentary info
	 */
	public JPanel createActiveSedentaryBox() {

		// Initialize Variables
		JLabel nameLabel = new JLabel("Daily Minutes");
		JLabel nameLabelA = new JLabel("ACTIVE");
		JLabel nameLabelS = new JLabel("SEDENTARY");
		JButton xSignButton = new JButton("x");
		final JPanel paneName = new JPanel();

		// Setup how x button looks like
		xSignButton.setFont(font);
		xSignButton.setLayout(null);
		xSignButton.setForeground(blueColour);
		//xSignButton.setBorder(null);
		xSignButton.setBounds(1,1,20,20);

		nameLabel.setFont(font3);
		nameLabel.setForeground(blueColour);
		nameLabel.setBounds(25,-12,500,50);

		// Setup how Active label looks like
		nameLabelA.setFont(font2);
		nameLabelA.setForeground(blueColour);
		nameLabelA.setBounds(10,30,500,50);

		// Setup how activeString will look like
		activeString.setFont(apiFont);
		activeString.setForeground(blueColour);
		activeString.setBounds(10,52,500,50);

		// Setup how Sedentary looks like
		nameLabelS.setFont(font2);
		nameLabelS.setForeground(blueColour);
		nameLabelS.setBounds(10,72,500,50);

		// Setup how sedString will look like
		sedString.setFont(apiFont);
		sedString.setForeground(blueColour);
		sedString.setBounds(10,94,500,50);

		// Setup how pane looks like
		paneName.setLayout(null);
		paneName.setBackground(Color.WHITE);
		paneName.setVisible(true);

		// Adding action when x button is pressed
		// Close the pane when pressed
		xSignButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				paneName.setVisible(false);
				BaseDashBoardUI.getFrame().remove(paneName);
				BaseDashBoard.addClosedTile("Active Minutes");
			}
		});

		// Add labels and button to the pane
		paneName.add(nameLabelA, SwingConstants.CENTER);
		paneName.add(nameLabelS, SwingConstants.CENTER);
		paneName.add(nameLabel, SwingConstants.CENTER);
		paneName.add(activeString, SwingConstants.CENTER);
		paneName.add(sedString, SwingConstants.CENTER);
		paneName.add(xSignButton);
		return paneName;
	}

	/**
	 * Method will create a box with Distance information
	 * @return JPanel with Distance info
	 */
	public JPanel createDistanceBox() {

		// Initilize Variables
		JLabel nameLabel = new JLabel("Distance(km)");
		JButton xSignButton = new JButton("x");
		final JPanel paneName = new JPanel();
		JLabel bestDay = new JLabel("BEST DAY:");
		JLabel lifeTime = new JLabel("LIFE TIME:");
		JLabel daily = new JLabel("DAILY:");

		// Setup the x button 
		xSignButton.setFont(font);
		xSignButton.setLayout(null);
		xSignButton.setForeground(blueColour);
		//xSignButton.setBorder(null);
		xSignButton.setBounds(1,1,20,20);

		// Setup the label
		nameLabel.setFont(font3);
		nameLabel.setForeground(blueColour);
		nameLabel.setBounds(25,-12,500,50);

		daily.setFont(font2);
		daily.setLayout(null);
		daily.setForeground(blueColour);
		daily.setBounds(10,13,100,50);

		// Setup how Daily distanceString will look like
		distanceDailyString.setFont(apiFont);
		distanceDailyString.setForeground(blueColour);
		distanceDailyString.setBounds(10,33,500,50);

		bestDay.setFont(font2);
		bestDay.setLayout(null);
		bestDay.setForeground(blueColour);
		bestDay.setBounds(10,55,100,50);

		// Setup how best distanceString will look like
		distanceBestString.setFont(apiFont);
		distanceBestString.setForeground(blueColour);
		distanceBestString.setBounds(10,75,500,50);

		lifeTime.setFont(font2);
		lifeTime.setLayout(null);
		lifeTime.setForeground(blueColour);
		lifeTime.setBounds(10,97,100,50);

		// Setup how total distanceString will look like
		distanceTotalString.setFont(apiFont);
		distanceTotalString.setForeground(blueColour);
		distanceTotalString.setBounds(10,117,500,50);

		paneName.setLayout(null);
		paneName.setBackground(Color.WHITE);
		paneName.setVisible(true);
		paneName.add(distanceBestString);
		paneName.add(distanceDailyString);
		paneName.add(distanceTotalString);
		paneName.add(xSignButton);
		paneName.add(nameLabel);
		paneName.add(bestDay);
		paneName.add(lifeTime);
		paneName.add(daily);

		// Adding action when x button is pressed
		// Close the pane when pressed
		xSignButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				paneName.setVisible(false);
				BaseDashBoardUI.getFrame().remove(paneName);
				BaseDashBoard.addClosedTile("Distance");
			}
		});
		paneName.add(xSignButton);
		return paneName;
	}

	/**
	 * Method will create a box with Floor information
	 * @return JPanel with Floor info
	 */
	public JPanel createFloorBox() {

		// Declare variables
		JLabel nameLabel = new JLabel("Floors");
		JButton xSignButton = new JButton("x");
		final JPanel paneName = new JPanel();
		JLabel bestDay = new JLabel("BEST DAY:");
		JLabel lifeTime = new JLabel("LIFE TIME:");
		JLabel daily = new JLabel("DAILY:");

		// Setup the x button
		xSignButton.setFont(font);
		xSignButton.setLayout(null);
		xSignButton.setForeground(blueColour);
		//xSignButton.setBorder(null);
		xSignButton.setBounds(1,1,20,20);

		// Setup the labels
		nameLabel.setFont(font3);
		nameLabel.setForeground(blueColour);
		nameLabel.setBounds(25,-12,500,50);

		daily.setFont(font2);
		daily.setLayout(null);
		daily.setForeground(blueColour);
		daily.setBounds(10,13,100,50);

		// Setup how Daily floorString will look like
		floorDailyString.setFont(apiFont);
		floorDailyString.setForeground(blueColour);
		floorDailyString.setBounds(10,33,500,50);

		bestDay.setFont(font2);
		bestDay.setLayout(null);
		bestDay.setForeground(blueColour);
		bestDay.setBounds(10,55,100,50);

		// Setup how best floorString will look like
		floorBestString.setFont(apiFont);
		floorBestString.setForeground(blueColour);
		floorBestString.setBounds(10,75,500,50);

		lifeTime.setFont(font2);
		lifeTime.setLayout(null);
		lifeTime.setForeground(blueColour);
		lifeTime.setBounds(10,97,100,50);

		// Setup how total floorString will look like
		floorTotalString.setFont(apiFont);
		floorTotalString.setForeground(blueColour);
		floorTotalString.setBounds(10,117,500,50);

		paneName.setLayout(null);
		paneName.setBackground(Color.WHITE);
		paneName.setVisible(true);
		paneName.add(floorBestString);
		paneName.add(floorDailyString);
		paneName.add(floorTotalString);
		paneName.add(xSignButton);
		paneName.add(nameLabel);
		paneName.add(bestDay);
		paneName.add(lifeTime);
		paneName.add(daily);

		// Adding action when x button is pressed
		// Close the pane when pressed
		xSignButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				paneName.setVisible(false);
				BaseDashBoardUI.getFrame().remove(paneName);
				BaseDashBoard.addClosedTile("Floors");
			}
		});
		paneName.add(xSignButton);
		return paneName;
	}

	/**
	 * Method will create a box with Step information
	 * @return JPanel with Step info
	 */
	public JPanel createStepBox() {

		// Declare variables
		JLabel nameLabel = new JLabel("Steps");
		JButton xSignButton = new JButton("x");
		final JPanel paneName = new JPanel();
		JLabel bestDay = new JLabel("BEST DAY:");
		JLabel lifeTime = new JLabel("LIFE TIME:");
		JLabel daily = new JLabel("DAILY:");

		// Setup the x button
		xSignButton.setFont(font);
		xSignButton.setLayout(null);
		xSignButton.setForeground(blueColour);
		//xSignButton.setBorder(null);
		xSignButton.setBounds(1,1,20,20);

		// Setup the labels
		nameLabel.setFont(font3);
		nameLabel.setForeground(blueColour);
		nameLabel.setBounds(25,-12,500,50);

		daily.setFont(font2);
		daily.setLayout(null);
		daily.setForeground(blueColour);
		daily.setBounds(10,13,100,50);

		// Setup how Daily stepString will look like
		stepDailyString.setFont(apiFont);
		stepDailyString.setForeground(blueColour);
		stepDailyString.setBounds(10,33,500,50);

		bestDay.setFont(font2);
		bestDay.setLayout(null);
		bestDay.setForeground(blueColour);
		bestDay.setBounds(10,55,100,50);

		// Setup how best stepString will look like
		stepBestString.setFont(apiFont);
		stepBestString.setForeground(blueColour);
		stepBestString.setBounds(10,75,500,50);

		lifeTime.setFont(font2);
		lifeTime.setLayout(null);
		lifeTime.setForeground(blueColour);
		lifeTime.setBounds(10,97,100,50);

		// Setup how total stepString will look like
		stepTotalString.setFont(apiFont);
		stepTotalString.setForeground(blueColour);
		stepTotalString.setBounds(10,117,500,50);

		paneName.setLayout(null);
		paneName.setBackground(Color.WHITE);
		paneName.setVisible(true);
		paneName.add(stepTotalString);
		paneName.add(stepDailyString);
		paneName.add(stepBestString);
		paneName.add(xSignButton);
		paneName.add(nameLabel);
		paneName.add(bestDay);
		paneName.add(lifeTime);
		paneName.add(daily);

		// Adding action when x button is pressed
		// Close the pane when pressed
		xSignButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				paneName.setVisible(false);
				BaseDashBoardUI.getFrame().remove(paneName);
				BaseDashBoard.addClosedTile("Steps");
			}
		});
		paneName.add(xSignButton);
		return paneName;
	}

} // End of Class
